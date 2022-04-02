<template>
    <div>
        <l-map
            class="map"
            :center="centre"
            :zoom="zoom"
            :zoom-animation="false"
            :fade-animation="false"
            :options="{
                zoomControl: false,
                wheelDebounceTime: 100,
            }"
            ref="map"
            @update:zoom="zoomUpdated"
            @update:center="centerUpdated"
        >
            <!-- Placement du selecteur de map en haut à droite -->
            <l-control-layers position="topright"></l-control-layers>

            <!-- TODO preload tile => edgeBuffer -->
            <l-tile-layer
                v-for="tileProvider in tileProviders"
                :key="tileProvider.name"
                :name="tileProvider.name"
                :visible="tileProvider.visible"
                :url="tileProvider.url"
                :attribution="tileProvider.attribution"
                layer-type="base"
            />

            <!-- Placement du controlleur de zoom en bas à droite -->
            <!-- Eviter les conflits avec le bouton d'affichage du descriptif de l'itinéraire -->

            <l-routing-machine
                :waypoints="waypoints"
                :coordonnees-itineraire="coordonneesItineraire"
                @update:routeSwitch="onRouteSwitchChange"
            />

            <!-- Bornes de recharge -->
            <l-marker-cluster
                :options="{
                    animate: false,
                    animteAddingMarkers: false,
                }"
            >
                <l-marker
                    v-model="bornesProche"
                    v-for="borne in bornesProche"
                    v-bind:key="borne.ID"
                    :lat-lng="[
                        borne.AddressInfo.Latitude,
                        borne.AddressInfo.Longitude,
                    ]"
                    :icon="icons.greyIcon"
                >
                    <l-tooltip>
                        <div class="chargeur-informations">
                            <p class="chargeur-titre">
                                {{ borne.AddressInfo.Title }}
                            </p>
                            <p class="chargeur-adresse">
                                {{ borne.AddressInfo.AddressLine1 }}
                            </p>
                            <p
                                v-if="
                                    borne.AddressInfo.Town !== null &&
                                    borne.AddressInfo.Postcode !== null
                                "
                                class="chargeur-complement"
                            >
                                {{ borne.AddressInfo.Town }},
                                {{ borne.AddressInfo.Postcode }}
                            </p>
                            <p>
                                <span
                                    v-for="connexion in borne.Connections"
                                    v-bind:key="connexion.ID"
                                >
                                    {{ connexion.ConnectionTypeID }}
                                </span>
                            </p>
                        </div>
                    </l-tooltip>
                </l-marker>
            </l-marker-cluster>
        </l-map>
    </div>
</template>

<script>
// Import des components
import {
    LMap,
    LTileLayer,
    LMarker,
    LTooltip,
    LControlLayers,
} from "vue2-leaflet";
import Vue2LeafletMarkerCluster from "vue2-leaflet-markercluster";

// Import du component de routing
import LRoutingMachine from "../components/LRoutingMachine";

// Code de telechargement des icones de markers
import { icon } from "leaflet";

import debounce from "lodash.debounce";

// URL des maps :
const url_light_theme = "https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png";
const url_dark_theme =
    "https://tiles.stadiamaps.com/tiles/alidade_smooth_dark/{z}/{x}/{y}{r}.png";
const url_sat =
    "https://server.arcgisonline.com/ArcGIS/rest/services/World_Imagery/MapServer/tile/{z}/{y}/{x}";

let url = "";

const credits =
    "Alset | " +
    '<a href="https://batiste-laloi.com" target="_blank">Batiste Laloi</a>' +
    " & " +
    '<a href="https://maxime-battu.fr" target="_blank">Maxime Battu</a>';

const darkThemeMq = window.matchMedia("(prefers-color-scheme: dark)");

if (darkThemeMq.matches) {
    url = url_dark_theme;
} else {
    url = url_light_theme;
}

export default {
    props: {
        coordonneesItineraire: {
            type: Object,
        },
    },
    components: {
        LMap,
        LTileLayer,
        LMarker,
        LTooltip,
        LRoutingMachine,
        "l-marker-cluster": Vue2LeafletMarkerCluster,
        LControlLayers,
    },
    data() {
        return {
            // Map
            url: url,
            tileProviders: [
                {
                    name: "💡 Light theme",
                    visible: true,
                    attribution: credits,
                    url: url_light_theme,
                },
                {
                    name: "🌑 Dark theme",
                    visible: false,
                    attribution: credits,
                    url: url_dark_theme,
                },
                {
                    name: "🌍 Satellite",
                    visible: false,
                    attribution: credits,
                    url: url_sat,
                },
            ],
            centre: this.centreParDefaut,
            zoom: 11,
            waypoints: [],
            icon: null,
            w_recharges: [],
            icons: {
                greyIcon: icon({
                    iconUrl:
                        "https://raw.githubusercontent.com/pointhi/leaflet-color-markers/master/img/marker-icon-2x-grey.png",
                    shadowUrl: "",
                    shadowSize: [0, 0],
                    iconSize: this.tailleIcone,
                }),
                redIcon: icon({
                    iconUrl:
                        "https://raw.githubusercontent.com/pointhi/leaflet-color-markers/master/img/marker-icon-2x-red.png",
                    shadowUrl: "",
                    shadowSize: [0, 0],
                    iconSize: this.tailleIcone,
                }),
                blueIcon: icon({
                    iconUrl:
                        "https://raw.githubusercontent.com/pointhi/leaflet-color-markers/master/img/marker-icon-2x-blue.png",
                    shadowUrl: "",
                    shadowSize: [0, 0],
                    iconSize: this.tailleIcone,
                }),
                purpleIcon: icon({
                    iconUrl:
                        "https://raw.githubusercontent.com/pointhi/leaflet-color-markers/master/img/marker-icon-2x-violet.png",
                    shadowUrl: "",
                    shadowSize: [0, 0],
                    iconSize: this.tailleIcone,
                }),
                orangeIcon: icon({
                    iconUrl:
                        "https://raw.githubusercontent.com/pointhi/leaflet-color-markers/master/img/marker-icon-2x-orange.png",
                    shadowUrl: "",
                    shadowSize: [0, 0],
                    iconSize: this.tailleIcone,
                }),
            },
            routeSwitch: null,
            threshold: 0.5,
            connexionsCompatible: {
                type2: {
                    connexions: [25, 1036],
                },
                superChargeur: {
                    connexions: [27],
                },
            },
            bornes: [],
            debounceBornesProche: [],
        };
    },
    beforeCreate() {
        this.centreParDefaut = [45.78433216234776, 4.869708582722543];
        //this.centreParDefaut = [46.514211736281354, 2.576609403696891]
        this.tailleIcone = [25, 41];

        if (navigator.geolocation) {
            navigator.geolocation.getCurrentPosition(
                (success) => {
                    this.centre = [
                        success.coords.latitude,
                        success.coords.longitude,
                    ];
                },
                (error) => {
                    console.warn(error.message);
                }
            );
        }
    },
    async mounted() {
        // await this.chargerBornes();
    },
    watch: {
        bornesProche: debounce(function () {
            this.debounceBornesProche = this.bornesProche;
        }, 80),
    },
    computed: {
        bornesProche: {
            get() {
                // Store in a array all points from this.bornesCoords inside the current map view

                const bornesProchesCentre = [];

                for (const borne of this.bornes) {
                    if (
                        // On ne prend que les bornes qui sont aux alentours du centre de  la carte
                        borne.AddressInfo.Latitude >
                            this.centre[0] - this.threshold &&
                        borne.AddressInfo.Latitude <
                            this.centre[0] + this.threshold &&
                        borne.AddressInfo.Longitude >
                            this.centre[1] - this.threshold &&
                        borne.AddressInfo.Longitude <
                            this.centre[1] + this.threshold
                    ) {
                        const connexionValide = borne.Connections.some(
                            (connection) => {
                                return this.verifierTypeConnexions(
                                    connection.ConnectionTypeID
                                );
                            }
                        );
                        if (connexionValide) {
                            bornesProchesCentre.push(borne);
                        }
                    }
                }

                return bornesProchesCentre;
            },
            set(bornesProche) {
                this.bornesProches = bornesProche;
            },
        },
    },
    methods: {
        /**
         * @param {Object} pointDeCharge
         * @param {Object} localisation
         */
        calculerDistance(pointDeCharge, localisation) {
            let R = 6371; // km
            let dLat = ((localisation.lat - pointDeCharge.lat) * Math.PI) / 180;
            let dLon = ((localisation.lon - pointDeCharge.lon) * Math.PI) / 180;
            pointDeCharge.lat *= Math.PI / 180;
            localisation.lat *= Math.PI / 180;

            let a =
                Math.sin(dLat / 2) * Math.sin(dLat / 2) +
                Math.sin(dLon / 2) *
                    Math.sin(dLon / 2) *
                    Math.cos(pointDeCharge.lat) *
                    Math.cos(localisation.lat); // haut
            let c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));
            let d = R * c;

            return d;
        },
        verifierTypeConnexions(idConnexion) {
            return (
                idConnexion !== null &&
                (this.connexionsCompatible.type2.connexions.includes(
                    idConnexion
                ) ||
                    this.connexionsCompatible.superChargeur.connexions.includes(
                        idConnexion
                    ))
            );
        },
        /**
         * Charges les bornes pour un centre donné
         * @param {[lat: number, long: number]} centre
         */
        calculerBornesProches(centre) {
            // Store in a array all points from this.bornesCoords inside the current map view

            const bornesProchesCentre = [];

            for (const borne of this.bornes) {
                if (
                    // On ne prend que les bornes qui sont aux alentours du centre de  la carte
                    borne.AddressInfo.Latitude > centre[0] - this.threshold &&
                    borne.AddressInfo.Latitude < centre[0] + this.threshold &&
                    borne.AddressInfo.Longitude > centre[1] - this.threshold &&
                    borne.AddressInfo.Longitude < centre[1] + this.threshold
                ) {
                    const connexionValide = borne.Connections.some(
                        (connection) => {
                            return this.verifierTypeConnexions(
                                connection.ConnectionTypeID
                            );
                        }
                    );
                    if (connexionValide) {
                        bornesProchesCentre.push(borne);
                    }
                }
            }

            return bornesProchesCentre;
        },
        /**
         * Mets à jour les bornes en fonction du zoom
         *
         * @param {HTMLElement}
         */
        zoomUpdated(zoom) {
            this.zoom = zoom;
        },
        /**
         * Mets à jour les bornes lors du déplacement sur la map
         *
         * @param {[number, number]} : coordonnées du nouveau centre
         */
        centerUpdated(centre) {
            this.centre = [centre.lat, centre.lng];
        },
        onRouteSwitchChange(routeSwitch) {
            this.routeSwitch = routeSwitch[0];
            this.$emit("update:routeSwitch", this.routeSwitch);

            this.w_recharges = routeSwitch[1];

            // Actualiser le tableau bornesData pour afficher les bornes proches des points de recharges
            this.bornesProche = [];

            // for (let i = 0; i < this.w_recharges.length; i++) {
            //     let re = this.w_recharges[i];
            //     // console.log(re);
            // }

            // Pour chaque item de w_recharges, on cherche la borne la plus proche
            for (let i = 0; i < this.w_recharges.length; i++) {
                let pointDeCharge = this.w_recharges[i];
                let borneLaPlusProche = null;
                let distanceLaPlusProche = null;
                for (let j = 0; j < this.bornesProche.length; j++) {
                    let localisation = this.bornesProche[j];

                    let distance = this.calculerDistance(
                        pointDeCharge,
                        localisation
                    );
                    if (!borneLaPlusProche || distance < distanceLaPlusProche) {
                        borneLaPlusProche = localisation;
                        distanceLaPlusProche = distance;
                    }
                }
                this.w_recharges[i].borneLaPlusProche = borneLaPlusProche;
                this.w_recharges[i].distanceLaPlusProche = distanceLaPlusProche;

                // On ajoute la borne la plus proche au tableau bornesProches
                this.bornesProche.push(borneLaPlusProche);

                // On supprime la borne la plus proche du tableau bornesData
                this.bornesProche.splice(
                    this.bornesProche.indexOf(borneLaPlusProche),
                    1
                );
            }
        },
        /**
         * charge les informations nécessaires sur les bornes
         */
        async chargerBornes() {
            const response = await fetch("/bornesChargement.json");
            const bornes = await response.json();
            this.bornes = bornes.map((borne) => {
                return {
                    AddressInfo: borne.AddressInfo,
                    Connections: borne.Connections.map((connection) => {
                        return {
                            ConnectionTypeID: connection.ConnectionTypeID,
                            ID: connection.ID,
                        };
                    }),
                };
            });
        },
    },
};
</script>

<style scoped>
.map {
    height: 100vh;
    width: 100%;
    z-index: 1;
}

.tooltip {
    padding: 0;
    color: none;
    border: none;
    border-radius: 25px;
    background-color: red;
}

.leaflet-pane .leaflet-marker-pane > img {
    box-shadow: none;
}

.chargeur-titre {
    font-family: "Roboto", sans-serif;
    font-size: 1.1rem;
    font-weight: 900;
    color: var(--indigo);
}

.chargeur-adresse,
.chargeur-complement {
    font-family: "Montserrat", sans-serif;
    font-size: 0.9rem;
    font-weight: 500;
}
</style>
