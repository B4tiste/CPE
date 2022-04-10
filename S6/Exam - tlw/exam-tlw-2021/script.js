// When the user scrolls down 20px from the top of the document, show the button
window.onscroll = function () {
    scrollFunction();
};

function scrollFunction() {
    if (
        document.body.scrollTop > 20 ||
        document.documentElement.scrollTop > 20
    ) {
        document.getElementById("myBtn").style.display = "block";
    } else {
        document.getElementById("myBtn").style.display = "none";
    }
}
// When the user clicks on the button, scroll to the top of the document
function topFunction() {
    document.body.scrollTop = 0;
    document.documentElement.scrollTop = 0;
}

let content = document.getElementById("visites");
for (const link of content.getElementsByTagName("a")) {
    link.style.color = "#666";
    link.style.textDecoration = "none";
}

function remplirActu() {
    console.log("Démarage de la fonction au chargement de la page");

    fetch("./actu.json")
        .then((response) => response.json())
        .then((data) => {

            let template = document.querySelector("#my_template");
            let grid = document.querySelector("#grid-container");

            for (const a of data.tableau_actu) {
                let clone = document.importNode(template.content, true);

                (newContent = clone.firstElementChild.innerHTML
                    .replace(/{{actu-image}}/g, a.image)
                    .replace(/{{actu-titre}}/g, a.titre)
                    .replace(/{{actu-texte}}/g, a.texte)
                    .replace(/{{actu-bouton}}/g, a.bouton)),
                    (clone.firstElementChild.innerHTML = newContent);

                grid.appendChild(clone);
            }
        })
        .catch((error) => console.log(error));
}

remplirActu()