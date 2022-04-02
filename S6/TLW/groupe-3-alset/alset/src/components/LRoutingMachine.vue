<template>
    <div style="display: none">
        <slot v-if="ready"></slot>
    </div>
</template>

<script>
import L from "leaflet";
import { IRouter, IGeocoder } from "leaflet-routing-machine";
import { findRealParent } from "vue2-leaflet";

// Import de la base de donnée des chargeurs en France
import BORNES from "../../data/bornesChargement.json";

const props = {
    visible: {
        // Permet de faire rentrer l'itinéraire dans la frame de la carte
        type: Boolean,
        default: true,
    },
    // waypoints: {
    //     type: Array,
    //     required: true,
    // },
    router: {
        type: IRouter,
    },
    draggableWaypoints: {
        type: Boolean,
        default: false, // Empecher le dragging des waypoints de l'itinéraire
    },
    plan: {
        type: L.Routing.Plan,
    },
    geocoder: {
        type: IGeocoder,
    },
    fitSelectedRoutes: {
        type: [String, Boolean],
        default: "smart",
    },
    routeLine: {
        type: Function,
    },
    autoRoute: {
        type: Boolean,
        default: true,
    },
    routeWhileDragging: {
        type: Boolean,
        default: false,
    },
    routeDragInterval: {
        type: Number,
        default: 500,
    },
    waypointMode: {
        type: String,
        default: "connect",
    },
    useZoomParameter: {
        type: Boolean,
        default: false,
    },
    showAlternatives: {
        type: Boolean,
        default: false,
    },
    addWaypoints: {
        type: Boolean,
        default: false,
    },
    coordonneesItineraire: {
        type: Object,
    },
};

export default {
    props,
    name: "LRoutingMachine",
    data() {
        return {
            parentContainer: null,
            ready: false,
            layer: null,
            nombre_pause: 0,
            recharges: [],
            autonomie_max: 250_000, // en mètres
            distance_parcourue: 0,
            bornesProches: [],
            bornesRecharge: [],
            waypoints: [],
            treshold: 0.5,
        };
    },
    beforeCreate() {
        // récupération du parent
        this.parentContainer = findRealParent(this.$parent);
    },
    mounted() {
        this.parentContainer = findRealParent(this.$parent);
        this.add();
        this.ready = true;
    },
    beforeDestroy() {
        return this.layer ? this.layer.remove() : null;
    },
    computed: {
        mapObject() {
            return this.parentContainer.mapObject;
        },
    },
    watch: {
        coordonneesItineraire(coordonneesItineraire) {
            const date = new Date();
            this.waypoints = [];
            this.waypoints.push(
                {
                    id: "depart",
                    lat: coordonneesItineraire.depart.coords.lat,
                    lon: coordonneesItineraire.depart.coords.lon,
                    date: date.toLocaleString(),
                },
                {
                    id: "destination",
                    lat: coordonneesItineraire.arrivee.coords.lat,
                    lon: coordonneesItineraire.arrivee.coords.lon,
                    date: date.toLocaleString(),
                }
            );

            // Actualisation des waypoints sur la carte
            this.layer.setWaypoints(this.waypoints);

            const corner1 = L.latLng(
                this.waypoints[0].lat,
                this.waypoints[0].lon
            );
            const corner2 = L.latLng(
                this.waypoints[1].lat,
                this.waypoints[1].lon
            );

            const bounds = L.latLngBounds(corner1, corner2);

            this.mapObject.fitBounds(bounds, { padding: [80, 80] });
        },
    },
    methods: {
        // Fonction qui permet de calculer la distance entre deux points sur une sphère, en utilisant la formule de Haversine
        calculerDistance(lat1, lon1, lat2, lon2) {
            let R = 6371; // km
            let dLat = ((lat2 - lat1) * Math.PI) / 180;
            let dLon = ((lon2 - lon1) * Math.PI) / 180;
            lat1 = (lat1 * Math.PI) / 180;
            lat2 = (lat2 * Math.PI) / 180;

            let a =
                Math.sin(dLat / 2) * Math.sin(dLat / 2) +
                Math.sin(dLon / 2) *
                    Math.sin(dLon / 2) *
                    Math.cos(lat1) *
                    Math.cos(lat2);
            let c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));
            let d = R * c;

            return d;
        },
        add() {
            const {
                waypoints,
                fitSelectedRoutes,
                autoRoute,
                routeWhileDragging,
                routeDragInterval,
                waypointMode,
                useZoomParameter,
                showAlternatives,
                draggableWaypoints,
                addWaypoints,
            } = this;

            if (this.parentContainer._isMounted) {
                const options = {
                    waypoints,
                    fitSelectedRoutes,
                    autoRoute,
                    routeWhileDragging,
                    routeDragInterval,
                    waypointMode,
                    useZoomParameter,
                    showAlternatives,
                    draggableWaypoints,
                    addWaypoints,
                    lineOptions: {
                        styles: [
                            { color: "black", opacity: 0.8, weight: 2 },
                            { color: "white", opacity: 0.8, weight: 6 },
                            { color: "red", opacity: 0.9, weight: 7 },
                        ],
                    },
                    altLineOptions: {
                        styles: [
                            { color: "black", opacity: 0.8, weight: 2 },
                            { color: "white", opacity: 0.8, weight: 6 },
                            { color: "darkgrey", opacity: 1, weight: 7 },
                        ],
                    },
                    show: false, // Cacher la liste des étapes dans le block de la liste d'étapes
                    language: "fr",
                };

                const { mapObject } = this.parentContainer;
                const routingLayer = L.Routing.control(options);
                routingLayer.addTo(mapObject);
                // hide the layer
                // routingLayer.hide();
                this.layer = routingLayer;

                // Envoie de l'itinéraire vers le bus
                // routeselected => event fired when an alternative route is selected
                // Listen to the 'routeselected' event and show the instructions in the console
                routingLayer.on("routeselected", (e) => {
                    // Création d'un objet JSON pour les instructions de l'itinéraire avec un ID par instruction pour le v-for de Liste.vue

                    const instructions = e.route.instructions.map(
                        (instruction, index) => {
                            return {
                                id: index,
                                text: instruction.text,
                                time: instruction.time,
                                type: instruction.type,
                            };
                        }
                    );

                    instructions.totalDistance = e.route.summary.totalDistance;
                    instructions.totalTime = e.route.summary.totalTime;
                    instructions.name = e.route.name;

                    // Ajout des points de non retour

                    // Reset du tableau recharges
                    this.recharges = [];

                    let autonomie = this.autonomie_max; // mètres

                    let i = 0;

                    while (
                        this.distance_parcourue < e.route.summary.totalDistance
                    ) {
                        this.distance_parcourue +=
                            e.route.instructions[i].distance;

                        i++;

                        if (i >= e.route.instructions.length) {
                            break;
                        }

                        if (autonomie - e.route.instructions[i].distance < 0) {
                            this.nombre_pause++;

                            this.recharges.push({
                                date: new Date().toLocaleString(),
                                lat: e.route.coordinates[
                                    e.route.instructions[i].index
                                ].lat,
                                lon: e.route.coordinates[
                                    e.route.instructions[i].index
                                ].lng,
                                id: "recharge #" + this.nombre_pause,
                                autonomie_restante: autonomie,
                            });

                            autonomie = this.autonomie_max;
                        }

                        autonomie -= e.route.instructions[i].distance;
                    }

                    // Envoie de l'itinéraire dans le bus
                    this.$emit("update:routeSwitch", [
                        instructions,
                        this.recharges,
                    ]);

                    // console.log("Recharges : ", this.recharges);

                    // Reset du tableau des bornes les plus proches des points de recharge
                    this.bornesProches = [];

                    // On récupère la borne la plus proche de chaque point dans this.recharges
                    for (let i = 0; i < this.recharges.length; i++) {
                        let distance = 100_000_000;

                        for (let j = 0; j < BORNES.length; j++) {
                            const borne = BORNES[j];

                            const distanceBorne = this.calculerDistance(
                                this.recharges[i].lat,
                                this.recharges[i].lon,
                                borne.AddressInfo.Latitude,
                                borne.AddressInfo.Longitude
                            );

                            if (distanceBorne < distance) {
                                distance = distanceBorne;
                                this.bornesProches[i] = {
                                    id: "Recharge #" + (i + 1),
                                    lat: borne.AddressInfo.Latitude,
                                    lon: borne.AddressInfo.Longitude,
                                    distance: distance,
                                };
                            }
                        }
                        // console.log(distance);
                    }

                    // console.log("Taille de bornesProches : ", this.bornesProches.length);

                    // On insère dans this.waypoints les points de recharge
                    let depart = this.waypoints[0];
                    let arrivee = this.waypoints[1];

                    this.waypoints = [depart, ...this.bornesProches, arrivee];

                    // console.log("Waypoints", this.layer.getWaypoints());
                    // console.log("Recharges après calcul", this.recharges);
                    // console.log("this.waypoints", this.waypoints);
                    // console.log("bornesProches", this.bornesProches);

                    // Utilisation de la fonction spliceWaypoints pour ajouter les points de recharge à l'itinéraire
                    console.log("e.route.waypoints", e.route.waypoints);
                    if (e.route.waypoints.length == 2) {
                        this.layer.setWaypoints(this.waypoints);
                        this.layer.route();
                    }
                });
            }
        },
    },
};
</script>

<style>
@import "../../node_modules/leaflet-routing-machine/dist/leaflet-routing-machine.css";
.leaflet-routing-container {
    visibility: hidden; /* Cacher le carré vide de la liste de étapes de l'itinéraire */
}
</style>