
const pathToLocFiles = "../localization/";
var elements = new Map();
var loc_files = new Map();
document.addEventListener("DOMContentLoaded", (event) => {
    initElements();
    setLocFiles();

});

function initElements()
{
    elements.set("title", getElementById("title"));
    elements.set("langs", getElementById("langs"));
    elements.set("description", getElementById("description"));
    elements.set("description", getElementById("description"));
    elements.set("lv-title", getElementById("lv-title"));
    elements.set("add-btn", getElementById("add-btn"));
    elements.set("edit-btn", getElementById("edit-btn"));
    elements.set("del-btn", getElementById("del-btn"));
    elements.set("list-view", getElementById("list-view"));

    //Check elements init
    console.log("Elements were succesfully inited:");
    elements.forEach((v, k ,m)=>
    {
        console.log(k);
    });
}

function setLocalization(localization)
{
    let file = loc_files[localization]
    
    //Set new title
    elements["title"].innerHTML = loc_files["title"]
    
    
}

function setLocFiles()
{
    fetch(pathToLocFiles + "loc_files.json")
    .then(resp => resp.json())
    .then(data => {
        for (const locFile in data) {
            fetch(pathToLocFiles + locFile)
            .then(resp => resp.json())
            .then(jsonData =>
                {
                    loc_files.set(locFile["language"], jsonData);
                })
            .catch(error => console.log(`Unable to parse: ${pathToLocFiles + locFile}`));
        }
    }).catch(error => console.error("Unable to fetch data about localization!"));

    console.log("Localization files parsed.")
}

function getElementById(elemId)
{
    return document.getElementById(elemId);
}