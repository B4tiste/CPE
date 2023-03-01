package com.example.app;

import androidx.appcompat.app.AppCompatActivity;
import androidx.databinding.DataBindingUtil;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import android.os.Bundle;

import com.example.app.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {
    private ActivityMainBinding binding;

    OnClickOnPokemonListener listener = new OnClickOnPokemonListener() {
        @Override
        public void onClickOnPokemon(Pokemon pokemon) {
            System.out.println("Click on " + pokemon.getName());
            showPokemonDetail(pokemon);
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = DataBindingUtil.setContentView(this, R.layout.activity_main);
        this.showStartup();
    }

    public void showStartup() {
        FragmentManager manager = getSupportFragmentManager();
        FragmentTransaction transaction = manager.beginTransaction();
        PokedexFragment fragment = new PokedexFragment();
        fragment.setListener(listener);
        transaction.replace(R.id.fragment_container,fragment);
        transaction.commit();
    }

    // Fonction qui affiche le détail d'un pokemon
    public void showPokemonDetail(Pokemon pokemon) {
        FragmentManager manager = getSupportFragmentManager();
        FragmentTransaction transaction = manager.beginTransaction();
        CartePokemonFragment fragment = new CartePokemonFragment();
        fragment.setPokemon(pokemon);
        transaction.addToBackStack(null);
        transaction.replace(R.id.fragment_container, fragment);
        transaction.commit();
    }
}