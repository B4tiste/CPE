package com.example.app;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.databinding.DataBindingUtil;
import androidx.fragment.app.Fragment;

import com.example.app.databinding.PokemonCarteFragmentBinding;

public class CartePokemonFragment extends Fragment {
    private Pokemon pokemon;

    public void setPokemon(Pokemon pokemon) {
        this.pokemon = pokemon;
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater,
                             @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        PokemonCarteFragmentBinding binding = DataBindingUtil.inflate(inflater,
                R.layout.pokemon_carte_fragment, container, false);

        return binding.getRoot();
    }
}
