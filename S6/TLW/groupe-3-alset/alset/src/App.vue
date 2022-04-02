<template>
    <div id="app">
        <!-- Carte -->
        <Map 
            :coordonnees-itineraire="coordonneesItineraire"
            @update:routeSwitch="onRouteSwitchChange"
        />         
        <!-- Affichage de la recherche d'itinéraire-->
        <AffichageItineraire /> 
        <div class="map-container">
            <div class="trajet active">
                <div class="champs-adresse">
                <ChampsAdresse 
                    label="Départ" 
                    label-placeholder="On va où ?"
                    @update:adresse="onDepartChange"
                />
                <ChampsAdresse 
                    label="Arrivée" 
                    label-placeholder="On arrive où ?" 
                    @update:adresse="onArriveeChange"
                />
                </div>
                
                <RechercheItineraire
                    :depart-adresse="departAdresse"
                    :arrivee-adresse="arriveeAdresse"
                    @update:coordonneesItineraire="onCoordonneesItineraireChange"
                />
            </div>
        </div>
        <ResumeItineraire 
            class="bornes"
            :route-switch="routeSwitch"
        />
        <BoutonBascule />
    </div>
</template>

<script>
import Map from "./components/Map.vue";
import ResumeItineraire from "./components/ResumeItineraire.vue";
import ChampsAdresse from "./components/ChampsAdresse.vue";
import BoutonBascule from "./components/BoutonBascule.vue"
import AffichageItineraire from "./components/AffichageItineraire.vue"
import RechercheItineraire from "./components/RechercheItineraire.vue";

export default {
    name: "App",
    components: {
    Map,
    ResumeItineraire,
    ChampsAdresse,
    BoutonBascule,
    AffichageItineraire,
    RechercheItineraire
},
    data() {
        return {
            routeSwitch:null,
            departAdresse:null,
            arriveeAdresse:null,
            coordonneesItineraire:null
        }
    },
    methods: {
        onRouteSwitchChange(routeSwitch) {
            this.routeSwitch = routeSwitch;
        },
        onDepartChange(departAdresse) {
            this.departAdresse = departAdresse;
        },
        onArriveeChange(arriveeAdresse) {
            this.arriveeAdresse = arriveeAdresse;
        },
        onCoordonneesItineraireChange(coordonneesItineraire) {
            this.coordonneesItineraire = coordonneesItineraire;
        }
    }
};
</script>

<style>
/* Import du css des clusters de marker */
@import "~leaflet.markercluster/dist/MarkerCluster.css";
@import "~leaflet.markercluster/dist/MarkerCluster.Default.css";

/* font family */
@import url("https://fonts.googleapis.com/css2?family=Montserrat&family=Roboto&display=swap");

:root {
    --white-bg: #FFFFFF;
    --black-bg:#03191E;
    --black-jungle:#06120e;
    --indigo:#3B0086; 
    --magenta: #6200B3;
    --manatee:#9999A1;
    --title-light:#03191E;
    --font-family-title: "Montserrat", sans-serif;
    --font-family-text: "Robot", sans-serif;
    --font-size-title:3rem;
    --font-size-subtitle:2rem;
    --font-size-text-important:1.5rem;
    --font-size-text:1rem;
}
/* réinitialisation du style de base */
*,
*::before,
*::after{
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}

html {
    /* référence du rem */
    font-size: 18px; 
}

body { 
    height:100vh;
    width: 100%;
    background-color: var(--white-bg);
}

.map-container {
    display: flex;
    flex-direction: column;
    justify-content:flex-start;
}

.trajet {
    display: flex;
    flex-direction: column;
    justify-content: center;
    position: absolute;
    top: -200px;
    left: 50%;
    width:100%;
    max-width: 700px;
    height:150px;    
    transform: translateX(-50%);
    align-items: center;
    background-color: var(--white-bg);
    box-shadow: 0px 0px 5px 0px var(--manatee) inset;
    border: 2px solid var(--manatee);
    border-radius: 100px;
    z-index: 100;
    transition: .5s top ease-in-out;
}


.trajet.active {
    top: 25px;
}

.champs-adresse {
    display: flex;
    flex-direction: row;
    width: 80%;
    justify-content: space-between;
}

@keyframes slideIn {
    0% {
        transform: translateX(-100%);
        visibility: hidden;
    }   
    100% {
        transform: translateX(0%);
        visibility: visible;
    }
}

@keyframes slideOut {
    0% {
        transform: translateX(0);
        visibility: visible;
    }  
    90% {
        visibility: hidden;
    } 
    100% {
        transform: translateX(-100%);
    }
}
</style>