<template>
  <div class="form">
    <label for="depart">{{ label }}</label>
    <input
      v-model="text"
      :placeholder="labelPlaceholder"
      id="depart"
    />
  </div>
</template>
<script>
import mapboxClient from '../services/MapboxClient';

export default {
    data() {
        return {
            text: ""
        };
    },
  props: {
    label: {
      required: true,
      type: String,
    },
    labelPlaceholder: {
      required: true,
      type: String,
    }
  },
  watch: {
    text(text) {
      this.$emit("update:adresse", text);
    }
  },
  methods: {
    async onClick() {
      if (this.text !== null && this.text.length > 0) {

        let coords;
        try {
          coords = await mapboxClient.getCoords(this.text);
        } catch (error) {
          alert(error);
          console.error(error);
          return;
        }
          
        // Création d'un objet :
        const departInfo = {
          coords: {
            lat: coords.features[0].center[1],
            lon: coords.features[0].center[0],
          },
          adresse: {
            adresseSaisie: this.text,
          },
        };

        // Envoie des coordonnées au parent (App.vue)
        this.$emit("update:adresse", departInfo);
      }
    }
  }
};
</script>

<style scoped>
.form {
    display: flex;
    flex-direction: column;
    justify-content: space-around;
    padding: 10px 0;
    font-size: var(--font-size-text);
}

.form label {
    color: var(--indigo);
    font-family: var(--font-family-title);
    font-size: var(--font-size-text);
    padding: 0 10px;
}

.form input {
    width: 100%;
    height: 30px;
    border: none;
    outline: none;
    font-size: var(--font-size-text);
    border-bottom: 2px solid var(--manatee);
    border-top-left-radius: 5px;
    border-top-right-radius: 5px;
    padding: 0 10px;
    transition: .5s;
}

.form input:focus {
    border: none;
    border-bottom: 2px solid var(--indigo);
    background-color: var(--white-bg);
    transform: scaleX(1) translateY(0px);
    transition: .5s;
}

</style>
