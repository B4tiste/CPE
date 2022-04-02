import Vue from "vue";
import App from "./App.vue";

import L from "leaflet";
import "leaflet/dist/leaflet.css";

import iconRetinaUrl from "leaflet/dist/images/marker-icon-2x.png";
import iconUrl from "leaflet/dist/images/marker-icon.png";
import shadowUrl from "leaflet/dist/images/marker-shadow.png";

// Import du CSS de leaflet
import "leaflet/dist/leaflet.css";
import "./styles/main.css";

delete L.Icon.Default.prototype._getIconUrl;

L.Icon.Default.mergeOptions({
    iconRetinaUrl,
    iconUrl,
    shadowUrl,
});

Vue.config.productionTip = false;

new Vue({
    render: (h) => h(App),
}).$mount("#app");
