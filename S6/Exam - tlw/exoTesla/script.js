function remplir_accessoires() {
    console.log("Démarage de la fonction au chargement de la page");

    fetch("./accessoires.json")
    .then((response) => response.json())
    .then((data) => {
        let tbl = data;
        console.log(tbl);
    })
    .catch((error) => console.log(error));
}
