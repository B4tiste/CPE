function remplir_accessoires() {
    console.log("Démarage de la fonction au chargement de la page");

    fetch("./accessoires.json")
        .then((response) => response.json())
        .then((data) => {

            let template = document.querySelector("#template_accessoires");
            let grid = document.querySelector("#grid-container");

            for (const a of data.tableau_accessoires) {
                let clone = document.importNode(template.content, true);

                (newContent = clone.firstElementChild.innerHTML
                    .replace(/{{accessoires-image}}/g, a.image)
                    .replace(/{{accessoires-titre}}/g, a.titre)
                    .replace(/{{accessoires-texte}}/g, a.texte)),
                    (clone.firstElementChild.innerHTML = newContent);

                grid.appendChild(clone);
            }
        })
        .catch((error) => console.log(error));
}

remplir_accessoires();
