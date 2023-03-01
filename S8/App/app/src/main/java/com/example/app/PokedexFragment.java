package com.example.app;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.databinding.DataBindingUtil;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;

import com.example.app.databinding.PokedexFragmentBinding;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

public class PokedexFragment extends Fragment {

    private OnClickOnPokemonListener listener;

    public void setListener(OnClickOnPokemonListener listener) {
        this.listener = listener;
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater,
                             @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        PokedexFragmentBinding binding = DataBindingUtil.inflate(inflater,
                R.layout.pokedex_fragment, container, false);
        binding.pokemonList.setLayoutManager(new LinearLayoutManager(
                binding.getRoot().getContext()));

        List<Pokemon> pokemonList = new ArrayList<>();

        // On utilise un fichier json pour ajouter tous les pokemons
        InputStreamReader isr = new InputStreamReader(getResources().openRawResource(R.raw.poke));
        BufferedReader reader = new BufferedReader(isr);
        StringBuilder sb = new StringBuilder();
        String data = "";

        //lecture du fichier. data == null => EOF
        while(data != null) {
            try {
                data = reader.readLine();
                sb.append(data);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        // On récupère les infos du fichier
        try {
            JSONArray arr = new JSONArray(sb.toString());

            for(int i = 0; i< arr.length(); i++) {
                JSONObject obj = arr.getJSONObject(i);
                int id = obj.getInt("id");
                String name = obj.getString("name");
                String image = obj.getString("image");
                String type1 = obj.getString("type1");
                String type2 = null;
                if (obj.has("type2"))
                    type2 = obj.getString("type2");

                int imageId = getResources().getIdentifier(image, "drawable", binding.getRoot().getContext().getPackageName());

                pokemonList.add(
                    new Pokemon(
                            id,
                            name,
                            imageId,
                            Pokemon.POKEMON_TYPE.valueOf(type1),
                            type2 == null ? null : Pokemon.POKEMON_TYPE.valueOf(type2)
                    )
                );
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }

        PokemonListAdapter adapter = new PokemonListAdapter(pokemonList);
        adapter.setOnPokemonClickListener(listener);
        binding.pokemonList.setAdapter(adapter);

        return binding.getRoot();
    }
}