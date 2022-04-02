<template>
    <div>
        <button type="button" :disabled="isDisabled" @click="setItineraire">Allez c'est parti !</button>
    </div>
</template>

<script>
import mapboxClient from '../services/MapboxClient';

export default {
    props: {
        departAdresse: {
            type: String
        },
        arriveeAdresse: {
            type: String
        }
    },
    computed: {
        isDisabled() {
            if (this.departAdresse != null && this.arriveeAdresse != null
                && this.departAdresse.length > 0 && this.arriveeAdresse.length > 0) {
                return false;
            }
            return true;
        }
    },
    methods: {
        async setItineraire() {
            if (this.departAdresse !== null && this.departAdresse.length > 0 && this.arriveeAdresse !== null && this.arriveeAdresse.length > 0) {

                let departCoords;
                let arriveeCoords;
                try {
                    departCoords = await mapboxClient.getCoords(this.departAdresse);
                    arriveeCoords = await mapboxClient.getCoords(this.arriveeAdresse);
                } catch (error) {
                    alert(error);
                    console.error(error);
                    return;
                }
                
                // Création d'un objet :
                const coordonneesItineraire = {
                    depart: {
                        coords: {
                            lat: departCoords.features[0].center[1],
                            lon: departCoords.features[0].center[0],
                        },
                        adresse: this.departAdresse
                    },
                    arrivee: {
                        coords: {
                            lat: arriveeCoords.features[0].center[1],
                            lon: arriveeCoords.features[0].center[0],
                        },
                        adresse: this.arriveeAdresse
                    }
                
                };
                // Envoie des coordonnées au parent (App.vue)
                this.$emit("update:coordonneesItineraire", coordonneesItineraire);
            }
        }
    }
}
</script>

<style scoped>
button {
    outline: none;
    align-self: center;
    width: 300px;
    height: 30px;
    border:2px solid var(--indigo) ;
    font-size: var(--font-size-text);
    background-color: var(--indigo);
    color: #FFF;
    border-radius: 50px;
    text-transform: uppercase;
    letter-spacing: 2px;
    cursor: pointer;
    margin: 10px 0;
    transition: .2s;
}

button:hover {
    color: #fff;
    border-color: var(--indigo) ;
    background-color: var(--magenta);
    transition: .3s;
}

button:disabled {
    background-color: #999999;
    cursor: not-allowed;
}
</style>