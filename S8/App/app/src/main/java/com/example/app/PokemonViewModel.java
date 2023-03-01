package com.example.app;

import android.content.Context;
import android.graphics.drawable.Drawable;

import androidx.core.content.res.ResourcesCompat;
import androidx.databinding.BaseObservable;
import androidx.databinding.Bindable;

public class PokemonViewModel extends BaseObservable {
    private Pokemon pokemon = new Pokemon();

    public void setPokemon(Pokemon pokemon) {
        this.pokemon = pokemon;
        notifyChange();
    }

    @Bindable
    public int getFrontResource() {
        return pokemon.getFrontResource();
    }

    @Bindable
    public String getName() {
        return pokemon.getName();
    }

    @Bindable
    public String getType1String() {
        return pokemon.getType1String();
    }

    @Bindable
    public String getType2String() {
        if (pokemon.getType2() != null) {
            return pokemon.getType2String();
        } else {
            return "";
        }
    }

    @Bindable
    public String getNumber() {
        return "#" + pokemon.getOrder();
    }

    public Drawable getImage(Context context, int res) {
        if (res != -1) {
            return ResourcesCompat.getDrawable(context.getResources(), res, context.getTheme());
        }
        else {
            return null;
        }
    }
}
