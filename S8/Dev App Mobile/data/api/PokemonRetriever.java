import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.security.SecureRandom;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Collections;
import java.util.Date;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.TimeZone;
import java.util.concurrent.Semaphore;

public class PokemonRetriever {

  private static Map<String, String> typeConversion = Map.ofEntries(
      Map.entry("normal", "Normal"),
      Map.entry("fighting", "Combat"),
      Map.entry("flying", "Vol"),
      Map.entry("poison", "Poison"),
      Map.entry("ground", "Sol"),
      Map.entry("rock", "Roche"),
      Map.entry("bug", "Insecte"),
      Map.entry("ghost", "Spectre"),
      Map.entry("steel", "Acier"),
      Map.entry("fire", "Feu"),
      Map.entry("water", "Eau"),
      Map.entry("grass", "Plante"),
      Map.entry("electric", "Electrique"),
      Map.entry("psychic", "Psy"),
      Map.entry("ice", "Glace"),
      Map.entry("dragon", "Dragon"),
      Map.entry("dark", "Tenebre"),
      Map.entry("fairy", "Fee"),
      Map.entry("unknown", "Inconnu"));

  public static void main(String[] args) {

    JSONArray pokemons = new JSONArray();

    for (int i = 1; i < 152; i++) {
      InputStream inStream = null;
      HttpURLConnection urlConnection = null;
      try {
        URL url = new URL("https://pokeapi.co/api/v2/pokemon/" + i);
        urlConnection = (HttpURLConnection) url.openConnection();
        urlConnection.setRequestProperty("Content-Type", "application/json");
        urlConnection.setRequestProperty("Accept", "application/json");
        urlConnection.setDoInput(true);
        inStream = urlConnection.getInputStream();
        String jsonStr = getJSON(inStream);
        JSONObject object = new JSONObject(jsonStr);
        int id = object.getInt("id");
        String name = getName(object.getJSONObject("species"));
        int height = object.getInt("height");
        int weight = object.getInt("weight");
        JSONArray types = object.getJSONArray("types");
        String type1 = getTypes(types.getJSONObject(0));
        String type2 = null;
        if (types.length() == 2)
          type2 = getTypes(types.getJSONObject(1));

        JSONObject pokemon = new JSONObject();
        pokemon.put("id", id);
        pokemon.put("name", name);
        pokemon.put("weight", weight / 10.0f);
        pokemon.put("height", height / 10.0f);
        pokemon.put("type1", type1);
        pokemon.put("image", "p" + i);
        if (type2 != null)
          pokemon.put("type2", type2);
        pokemons.put(pokemon);
      } catch (Exception e) {
        e.printStackTrace();
        if (urlConnection != null)
          inStream = urlConnection.getErrorStream();
      }

      try {
        if (inStream != null)
          inStream.close();
      } catch (IOException e) {
        e.printStackTrace();
      }

    }
    System.out.println(pokemons.toString());
  }

  private static String getJSON(InputStream stream) {
    InputStreamReader isr = new InputStreamReader(stream);
    BufferedReader br = new BufferedReader(isr);
    boolean isReading = true;
    String data;
    StringBuilder builder = new StringBuilder();
    // get all data in a String
    do {
      try {
        data = br.readLine();
        if (data != null)
          builder.append(data);
        else
          isReading = false;
      } catch (IOException e) {
        e.printStackTrace();
        isReading = false;
      }
    } while (isReading);
    return builder.toString();
  }

  private static String getTypes(JSONObject object) throws JSONException {
    JSONObject type = object.getJSONObject("type");
    String typeStr = type.getString("name");
    return typeConversion.get(typeStr);
  }

  private static String getName(JSONObject species) throws JSONException {
    String name = null;
    try {
      String speciesUrl = species.getString("url");
      URL url = new URL(speciesUrl);
      InputStream inStream = null;
      HttpURLConnection urlConnection = null;
      urlConnection = (HttpURLConnection) url.openConnection();
      urlConnection.setRequestProperty("Content-Type", "application/json");
      urlConnection.setRequestProperty("Accept", "application/json");
      urlConnection.setDoInput(true);
      inStream = urlConnection.getInputStream();
      String jsonStr = getJSON(inStream);
      JSONObject object = new JSONObject(jsonStr);
      JSONArray names = object.getJSONArray("names");
      if (names.length() >= 4)
        name = names.getJSONObject(4).getString("name");
      else
        name = object.getString("name");
    } catch (IOException e) {
      e.printStackTrace();
    }
    return name;
  }

}
