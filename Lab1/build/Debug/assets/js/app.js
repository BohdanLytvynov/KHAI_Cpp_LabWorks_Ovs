var loc_files = new Map();
var first_lang = "";

// let json = '[{"language":"English","main-page":{"title":"Lab Work 1","langs":[{"disp-name":"English","value":"English"},{"disp-name":"Ukrainian","value":"Ukrainian"}],"description":"Here is our Juce Store. You can use it store different type of juces. Use buttons Add, Edit and Remove to manipulate the data.","lv-title":"Juce List:","buttons":{"add-btn":"Add","edit-btn":"Edit","del-btn":"Remove"}},"add-offcanv":{},"edit-offcanv":{}}]';

// document.addEventListener("DOMContentLoaded", event => 
// {
//     setLocalizationFiles(json)
// });

function createBindings()
{    
    //Set Reactive Function for Select Language
    getElementById("langs").addEventListener("change", (event) =>{        
        setLocalization(language);
    });
}

function setLocalization(localization)
{
    let file = loc_files.get(localization)
    let mainPage = file["main-page"]
    //Set new title
    getElementById("title").innerHTML = mainPage["title"]    
    //Set languages
    let langs = mainPage["langs"]       
    let count = langs.length;
    
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
//data - array of Files with localizations in JSON Format
function setLocalizationFiles(locFiles)
{
    let index = 0;
    for (const elem of locFiles) {
        let jObject = JSON.parse(elem)
        if(index == 0)
        {                 
            first_lang = jObject["language"]
        }
        loc_files.set(jObject["language"], jObject);   
        index++; 
    }        

    FillLangSelector()
}

function FillLangSelector()
{
    if(loc_files.length == 0) return
        
    let langObj = loc_files.get(first_lang)
    let mainPage = langObj["main-page"]
    let languages = mainPage["langs"]
    let lSelect = getElementById("langs");
    languages.forEach(l => {
        let option = document.createElement("option")
        option.innerHTML = l["disp-name"]
        option.value = l["value"]
        lSelect.appendChild(option)        
    });
}

function getElementById(elemId)
{
    return document.getElementById(elemId);
}