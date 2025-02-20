 
var loc_files = new Map();
var first_lang = "";

let json = ['{"language":"English","main-page":{"title":"Lab Work 1","langs-select":"Select the language you want please:","langs":[{"disp-name":"English","value":"English"},{"disp-name":"Ukrainian","value":"Ukrainian"}],"description":"Here is our Juce Store. You can use it store different type of juces. Use buttons Add, Edit and Remove to manipulate the data.","lv-title":"Juce List:","buttons":{"add-btn":"Add","edit-btn":"Edit","del-btn":"Remove"}},"add-offcanv":{"juce-name-label":"Enter Juce Name:","juce-manufacturer-label":"Enter Juce Manufacturer:","juce-volume-label":"Enter Juce volume:","add-juce-btn":"Add","clear-juce-btn":"Clear","back-to-main-btn":"Back"},"edit-offcanv":{"juce-name-label-edit":"Edit Juce Name:","juce-manufacturer-label-edit":"Edit Juce Manufacturer:","juce-volume-label-edit":"Edit Juce volume:","save-juce-btn-edit":"Save","clear-juce-btn-edit":"Clear","back-to-main-btn-edit":"Back"}}', '{"language":"Ukrainian","main-page":{"title":"Лабораторна робота номер 1","langs-select":"Виберіть мову, яку ви бажаєте:","langs":[{"disp-name":"Англійська","value":"English"},{"disp-name":"Українська","value":"Ukrainian"}],"description":"Це наше сховище соків. Ви можете додавати, редагувати та видаляти соки використовуючи відповідні кнопки знизу.","lv-title":"Список соків:","buttons":{"add-btn":"Додати","edit-btn":"Редагувати","del-btn":"Видалити"}},"add-offcanv":{"juce-name-label":"Введіть назву сока:","juce-manufacturer-label":"Введіть назву виробника сока:","juce-volume-label":"введіть обєм сока:","add-juce-btn":"Додати","clear-juce-btn":"Очистити","back-to-main-btn":"Назад"},"edit-offcanv":{"juce-name-label-edit":"Редагувати назву сока:","juce-manufacturer-label-edit":"Редагувати виробника сока:","juce-volume-label-edit":"Редагувати обєм сока:","save-juce-btn-edit":"Зберегти","clear-juce-btn-edit":"Очистити","back-to-main-btn-edit":"Назад"}}']

document.addEventListener("DOMContentLoaded", event => 
{   
    setLocalizationFiles(json)
    createBindings()
});

function createBindings()
{    
    //Set Reactive Function for Select Language
    getElementById("langs").addEventListener("change", (event) =>{         
        let selElement = event.target
        let lang = selElement.value
                
        setLocalization(lang)

        lang_current = lang       
        selectCurrentLanguage()                                
    });

    getElementById("clear-juce-btn").addEventListener("click", (event) =>
        {
            getElementById("juce-name").value = ""
            getElementById("juce-manufacturer").value = ""
            getElementById("juce-volume").value = ""
        }
    )

    getElementById("clear-juce-btn-edit").addEventListener("click", (event) =>
        {
            getElementById("juce-name-edit").value = ""
            getElementById("juce-manufacturer-edit").value = ""
            getElementById("juce-volume-edit").value = ""
        }
    )

    getElementById("add-juce-btn").addEventListener("click", (event) =>
        {
            let name = getElementById("juce-name").value
            let manuf = getElementById("juce-manufacturer").value
            let volume = getElementById("juce-volume").value

            addJuce(name, manuf, volume);
        }
    )    
}

function addJuce(juceName, juceManufacturer, juceVolume)
{
    if(juceName && juceManufacturer && juceVolume)
    {        
                
    }
}

function selectCurrentLanguage()
{
    let lSelect = getElementById("langs")               
    if(lSelect.hasChildNodes())
    {
        let children = lSelect.getElementsByTagName("option")
        let count = children.length
        for(let i = 0; i < count; ++i)
        {
            children[i].setAttribute('selected', false)            
        }

        for(let i = 0; i < count; ++i)
        {
            if(children[i].value === lang_current)
            {      
                console.log(`Selected language: ${children[i].value}`)
                console.log(`current lang: ${lang_current}`)                        
                children[i].setAttribute('selected', true)          
            }
        }
    }
    
}

function setLocalization(localization)
{    
    let file = loc_files.get(localization)  
   
    if(file)
    {        
        let mainPage = file["main-page"]
        if(!mainPage)
        {
            console.error("Unable to get main-page section from the localization file!")
            return
        }
        //Set new title
        getElementById("title").innerHTML = mainPage["title"]   
        //Set langs label
        getElementById("sel-label").innerHTML = mainPage["langs-select"]
        //Set languages
        FillLangSelector(file)    
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
        //Localization of the add offcanvas
        let addOffCanv = file["add-offcanv"]
        if(!addOffCanv)
        {
            console.error("Unable to get add-offcanv section from the localization file!")
            return
        }
        getElementById("juce-name-label").innerHTML = addOffCanv["juce-name-label"]
        getElementById("juce-manufacturer-label").innerHTML = addOffCanv["juce-manufacturer-label"]
        getElementById("juce-volume-label").innerHTML = addOffCanv["juce-volume-label"]
        getElementById("add-juce-btn").innerHTML = addOffCanv["add-juce-btn"]
        getElementById("clear-juce-btn").innerHTML = addOffCanv["clear-juce-btn"]
        getElementById("back-to-main-btn").innerHTML = addOffCanv["back-to-main-btn"]
        //Localization of the edit offcanvas
        let editOffCanv = file["edit-offcanv"]
        if(!editOffCanv)
        {
            console.error("Unable to get editOffCanv section from the localization file!")
            return
        }
        getElementById("juce-name-label-edit").innerHTML = editOffCanv["juce-name-label-edit"]
        getElementById("juce-manufacturer-label-edit").innerHTML = editOffCanv["juce-manufacturer-label-edit"]
        getElementById("juce-volume-label-edit").innerHTML = editOffCanv["juce-volume-label-edit"]
        getElementById("save-juce-btn-edit").innerHTML = editOffCanv["save-juce-btn-edit"]
        getElementById("clear-juce-btn-edit").innerHTML = editOffCanv["clear-juce-btn-edit"]
        getElementById("back-to-main-btn-edit").innerHTML = editOffCanv["back-to-main-btn-edit"]

    }   
    else
    {
        console.error(`Unable to find Localization file with key: ${localization} Function: setLocalization`)
    }        
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

    setLocalization(first_lang)
}

function FillLangSelector(loc_file)
{     
    if(!loc_file) return
            
    let mainPage = loc_file["main-page"]
    let languages = mainPage["langs"]
    let lSelect = getElementById("langs");
    //Clear options if they exists
    if(lSelect.hasChildNodes())
    {               
        let child = lSelect.lastElementChild;
        while (child) {
            lSelect.removeChild(child);
            child = lSelect.lastElementChild;
        }
    }

    languages.forEach((l) => {
        let option = document.createElement("option")
        option.innerHTML = l["disp-name"]
        option.value = l["value"]        
        lSelect.appendChild(option)        
    });  
}

function getElementById(elemId)
{
    let elem = document.getElementById(elemId);

    if(!elem) 
    {
        console.error(`Unable to locate element with id: ${elemId}! Function - getElementById(elemId)`)
        return undefined
    }
    
    return elem
}

