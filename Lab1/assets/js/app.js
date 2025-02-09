
var loc_files = new Map();

function createBindings()
{    
    //Set Reactive Function for Select Language
    getElementById("langs").addEventListener("change", (event) =>{
        let language = elements["langs"].value;
        setLocalization(language);
    });
}

function setLocalization(localization)
{
    let file = loc_files[localization]
    let mainPage = file["main-page"]
    //Set new title
    getElementById("title").innerHTML = mainPage["title"]    
    //Set languages
    let langs = mainPage["langs"]
    
    let count = langs.length;

    for(let i = 0; i < count; i++)
    {
        let opt = document.createElement("option");
        if(i === 0) 
        {
            opt.selected = true;            
        }

        opt.innerHTML = langs[i];
        opt.value = langs[i];

        getElementById("langs").appendChild(opt);
    }

    //Set description
    getElementById("description").innerHTML = mainPage["description"]
    //Set List View Title
    getElementById("lv-title").innerHTML = mainPage["lv-title"]
    let buttons = mainPage["buttons"]
    //Set Add Button
    getElementById("add-btn").innerHTML = buttons["add-btn"]
    //Set edit button
    getElementById("edit-btn").innerHTML = buttons["edit-btn"]
    //Set dlete button
    getElementById("del-btn").innerHTML = buttons["del-btn"]

}
//data - an array of localization settings
function setLocalizationFiles(data)
{
    for (let locFile in data)         
    {
        loc_files.set(locFile["language"], locFile);            
    }
}

function getElementById(elemId)
{
    return document.getElementById(elemId);
}