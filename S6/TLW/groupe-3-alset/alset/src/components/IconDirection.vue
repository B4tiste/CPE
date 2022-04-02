<template>
    <span>
        <img v-if="direction === 'Left'" src="../assets/icons-direction/left.png" alt="gauche" />
        <img v-if="direction === 'Right'" src="../assets/icons-direction/right.png" alt="droite" />
        <img v-if="direction === 'SlightLeft'" src="../assets/icons-direction/slideRight.png" alt="placer à droite" />
        <img v-if="direction === 'SlightRight'" src="../assets/icons-direction/slideLeft.png" alt="placer à gauche" />
        <img v-if="direction === 'StartAt' || direction === 'Head'" src="../assets/icons-direction/startAt.png" alt="débute ici" />
        <img v-if="direction === 'TurnAround'" src="../assets/icons-direction/turnAround.png" alt="demi tour" />
        <img v-if="direction === 'DestinationReached'" src="../assets/icons-direction/destinationReached.png" alt="arrivée" />
        <img v-if="direction === 'WaypointReached'" src="../assets/icons-direction/waypointReached.png" alt="pause" />
        <img v-if="direction === 'SharpLeft'" src="../assets/icons-direction/sharpLeft.png" alt="légèrement à gauche" />
        <img v-if="direction === 'SharpRight'" src="../assets/icons-direction/sharpRight.png" alt="légèrement à droite" />
        <img v-if="direction === 'Roundabout'" src="../assets/icons-direction/roundAbout.png" alt="faire le tour" />
        <img v-if="direction === 'Straight' || direction === 'Continue'|| direction === 'Fork' || direction === 'OffRamp' ||direction === 'Merge'" src="../assets/icons-direction/straight.png" alt="tout droit" />
        <img v-if="direction === 'EnterAgainstAllowedDirection'" src="../assets/icons-direction/interdiction.png" alt="tout droit" />
        <img v-if="direction === 'LeaveAgainstAllowedDirection'" src="../assets/icons-direction/interdiction.png" alt="tout droit" />
    </span>
</template>
<script>

export default {
    props: {
        direction: {
            type: String,
        }
    }
}
</script>
<style scoped>
span img {
    margin: 5px 10px 0 0;
}
</style>