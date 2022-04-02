<template>
<div class="trajet-container">
    <div class="resume-etape">
        <div class="resume-title">
            <p>étapes</p>
        </div>
        <div v-if="listeInstructions.name !== ''" class="etape-trajet">
            En passant par
            <span class="info-etape">{{ listeInstructions.name }}</span>
        </div>
        <div class="etapes">
            <div v-for="instruction in listeInstructions" v-bind:key="instruction.id">
                <div class="etape-instruction">
                    <IconDirection 
                        :direction="instruction.type"
                    />
                    {{ instruction.text }}
                </div>
                <div class="etape-temps">
                    <span class="strong">{{ conversionSecondes(instruction.time) }}</span>
                </div>
            </div>
        </div>
    </div>
    <div class="resume-trajet">
        <div class="trajet-previsions">
            <div><span class="info-previsions">{{ conversionMetre(listeInstructions.totalDistance) }}</span></div>
            <div>
                <span class="info-previsions point">
                    <svg height="8" width="8">
                        <circle cx="4" cy="4" r="4" fill="var(--indigo)" />
                    </svg>    
                </span>
            </div>
            <div><span class="info-previsions">{{ conversionSecondes(listeInstructions.totalTime) }}</span></div>
        </div>
        <div class="trajet-arrivee">
            <p>J'arriverais à <span class="heure-arrivee">{{calculHeureArrivee(listeInstructions.totalTime)}}</span> avec <span class="heure-arrivee">XX%</span></p>
        </div>
    </div>
</div>
</template>

<script>
import IconDirection from './IconDirection.vue'

let listeInstructions = "";

export default {
    components: {
        IconDirection
    },
    direction: "",
    listeInstructions: listeInstructions,
    adresseDepart: "",
    adresseArrivee: "",
    props: {
        departInfo: {
            type: Object
        },
        arriveeInfo: {
            type: Object
        },
        routeSwitch: {
            type: Array
        },
        direction: {
            type: String
        }
    },
    data() {
        return {
            listeInstructions: ""
        };
    },
    updated() {
        this.chargementInstructionsDOM();
    },
    watch: {
        departInfo(departInfo) {
            this.adresseDepart = departInfo.adresse.adresseSaisie
        },
        arriveeInfo(arriveeInfo) {
            this.adresseArrivee = arriveeInfo.adresse.adresseSaisie
        },
        routeSwitch(routeSwitch) {
            this.listeInstructions = routeSwitch;
        }
    },
    methods: {
        /**
         * Convertit une durée en seconde au format xxhxx
         * 
         * @param {number} durée en seconde
         * @return {string} la durée au format xxhxx
         */
        conversionSecondes(duree) {
            let heure = Math.floor(duree / 3600);
            let minute = Math.floor(duree % 3600 / 60);

            if (duree < 60) {
                return '< 1m'
            }

            if (heure === 0) {
                return minute + 'm';
            }

            return heure + 'h ' + ('0' + minute).slice(-2) + 'm';
        },
        calculHeureArrivee(duree) {
            let date = new Date()
            let heureActuelle = date.getHours();
            let minuteActuelle = date.getMinutes();

            let heure = Math.floor(duree / 3600);
            let minute = Math.floor(duree % 3600 / 60);

            let heureCpt = heureActuelle + heure;
            let minuteCpt = minuteActuelle + minute

            if (minuteCpt >= 60) {
                heureCpt++
                minuteCpt -= 60;
            }

            if (heureCpt >= 24) {
                heureCpt = 0
            }

            return (('0' + heureCpt).slice(-2) + ':' + ('0' + minuteCpt).slice(-2)).replace(':', 'h');
        },
        /**
         * Convertit une distance en mètre pour la rendre au format xx,xkm
         * 
         * @param {number} la distance en m
         * @return {string} la distance au format xx,xkm
         */
        conversionMetre(distance) {
            let km = Math.floor(distance / 1000);
            let metre = Math.floor(distance % 1000);

            let nouveauMetre = metre % 50
            if (metre > (50 / 2)) {
                metre += (50 - nouveauMetre)
            } else {
                metre -= nouveauMetre
            }

            return km + ',' + ('0' + metre).slice(-2) + 'km'
        },
        /**
         * Attends le chargement complet des instructions, afin d'afficher leurs informations complémentaires
         */
        chargementInstructionsDOM() {
            let menu = document.querySelector('.goOut')
            menu.classList.add('show')

            menu.addEventListener('click', () => {
                menu.classList.toggle('active')
            })

            let instructions = document.querySelectorAll('.etape-instruction')
            instructions.forEach(instruction => {
                instruction.addEventListener('click', () => {
                    instruction.nextSibling.classList.toggle('reveal');
                })
            });
        },
        reinitialisationStyleElmCache() {
            let elementsCaches = document.querySelectorAll('.etape-temps')
            elementsCaches.forEach(etape => {
                if (etape.classList.contains('reveal')) {
                    etape.classList.remove('reveal');
                }
            })
        }

    }
};
</script>

<style scoped>
@import url('https://fonts.googleapis.com/css2?family=Saira+Condensed:wght@300&display=swap');

.bornes {
    visibility: hidden;
    position: absolute;
    top: 0;
    left: 0;
    transform: translateX(-100%);
    min-height: 100vh;
    width: 450px;
    background-color: var(--white-bg);
    z-index: 100;
    animation: slideOut .5s;
}

.bornes.active {
    visibility: visible;
    transform: translateX(0);
    animation: slideIn .5s;
}

/* Bloc container */
.trajet-container {
    display: flex;
    flex-direction: column;
    justify-content: space-evenly;
    height: 100vh;
    padding: 20px 30px;
}

/* premier enfant contenant les instructions */
.resume-etape {
    display: flex;
    flex-direction: column;
    justify-content: space-between;
    position: relative;
    height: 80%;
    width: 100%;
}

/* deuxième enfant contenant le résumé des informations sur le trajet */
.resume-trajet {
    position: relative;
    height: 15%;
    display: flex;
    justify-content: space-around;
    flex-direction: column;
}

.resume-title {
    display: block;
    width: 100%;
    text-transform: uppercase;
    color: var(--indigo);
    font-family: var(--font-family-title);
    font-size: var(--font-size-subtitle);
    letter-spacing: 1px;
    align-self: center;
}


.etape-trajet,
.etape-instruction,
.trajet-previsions,
.trajet-arrivee {
    font-family: var(--font-family-text);
    font-size: var(--font-size-text);
}

.etapes {
    height: 80%;
    overflow-y: scroll;
    padding-right: 5px;
}

.etape-instruction {
    font-size: var(--font-size-text);
    cursor: pointer;
}

.etape-instruction:first-child {
    padding-top: 10px;
}

.etape-temps {
    visibility: hidden;
    position: relative;
    display: flex;
    justify-content: flex-end;
    width: 80%;
    height: 0;
    margin: 5px 0;
    color: var(--black-jungle);
    animation: hide .2s ease-in;
}

.etape-temps.reveal {
    visibility: visible;
    height: 100%;
    /* animation: reveal .2s ease-in; */
}

.etape-temps::before {
    content: '';
    position: absolute;
    top: 50%;
    left: 5%;
    height: 1px;
    width: 80%;
    background-color: var(--indigo);
}

.etape-trajet {
    font-style: italic;
}

.trajet-previsions {
    display: flex;
    width: 100%;
    justify-content: space-evenly;
}

.trajet-arrivee {
    display: flex;
    justify-content: flex-end;
    margin-top: 10px;
    font-size: var(--font-size-text-important);
}

.heure-arrivee,
.info-previsions,
.info-etape {
    font-family: 'Saira Condensed', sans-serif;
    color: var(--indigo);
}

.heure-arrivee,
.info-previsions {
    font-size: var(--font-size-subtitle);
    letter-spacing: 1px;
}

.info-previsions .point {
    font-size: 52px;
}

.info-etape {
    font-size: var(--font-size-text-important);
    font-style: initial;
}

.strong {
    font-weight: bold;
}

::-webkit-scrollbar {
    width: 4px;
}

/* Track */
::-webkit-scrollbar-track {
    background: var(--white-bg);
}

/* Handle */
::-webkit-scrollbar-thumb {
    background: var(--indigo);
    opacity: 0.7;
}

/* Handle on hover */
::-webkit-scrollbar-thumb:hover {
    background: var(--magenta);
    opacity: 0.3;
}

@keyframes reveal {
    0% {
        transform: translateY(-5px);
    }

    100% {
        transform: translateY(0);
    }
}

@keyframes hide {
    0% {
        visibility: visible;
        transform: translateY(0);
    }

    100% {
        visibility: hidden;
        transform: translateY(-10px);
    }
}
</style>
