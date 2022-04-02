<template>
    <div>
        <div class="popup-trajet active" @click="showItinariesSearching">
            <img class="rotate up" src="../assets/images/icons/chevron-en-haut.png" alt="chevron">
        </div>
    </div>
</template>

<script>
export default {
    methods: {
        showItinariesSearching() {
            let trajet = document.querySelector('.trajet');
            let chevron = document.querySelector('.rotate')


            trajet.classList.toggle('active');
            chevron.classList.toggle('up');
        }  
    }
}
</script>

<style scoped>

.popup-trajet {
    position: absolute;
    top: 0;
    left: 50%;
    transform: translate(-50%,-15px);
    min-width: 50px;
    height: 35px;
    border-bottom-left-radius: 20px;
    border-bottom-right-radius: 20px;
    background-color: var(--white-bg);
    border: 2px solid var(--manatee);
    border-top: none;
    box-shadow: 0px 0px 3px 0px var(--manatee);
    z-index: 150;
    cursor: pointer;
    text-align: center;
    transition: .3s;
}

.popup-trajet::after {
    visibility: hidden;
    content: "Recherche d'itinéraire";
    position: absolute;
    top: 5px;
    left: 55px;
    width: 190px;
    padding: 3px;
    background-color: var(--white-bg);
    color: var(--indigo);
    font-family: var(--font-family-title);
    font-size: 12px;
    font-weight: bold;
}

.popup-trajet:hover::after {
    visibility: visible;
    transition: .3s;
}

.rotate {
    transform: translateY(15px);
    height: 15px;
    transition: .3s;
}

.popup-trajet:hover {
    transform: translate(-50%,-1px);
}

.rotate.up {
    transform: translateY(15px) rotate(180deg);
    transition: .3s;
}
</style>