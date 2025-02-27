 
var loc_files = new Map();
var first_lang = "";
var selectedJuce = "-1";//Juce selected on the View
var selectedId = -1
var validation = new Map();

var canAdd = false
var canEdit = false
var canDelete = false;

//Used for testing
let json = ['{"language":"English","main-page":{"title":"Lab Work 1","langs-select":"Select the language you want please:","langs":[{"disp-name":"English","value":"English"},{"disp-name":"Ukrainian","value":"Ukrainian"}],"description":"Here is our Juce Store. You can use it store different type of juces. Use buttons Add, Edit and Remove to manipulate the data.","lv-title":"Juce List:","buttons":{"add-btn":"Add","edit-btn":"Edit","del-btn":"Remove"}},"add-offcanv":{"juce-name-label":"Enter Juce Name:","juce-manufacturer-label":"Enter Juce Manufacturer:","juce-volume-label":"Enter Juce volume:","add-juce-btn":"Add","clear-juce-btn":"Clear","back-to-main-btn":"Back"},"edit-offcanv":{"juce-name-label-edit":"Edit Juce Name:","juce-manufacturer-label-edit":"Edit Juce Manufacturer:","juce-volume-label-edit":"Edit Juce volume:","save-juce-btn-edit":"Save","clear-juce-btn-edit":"Clear","back-to-main-btn-edit":"Back"}}', '{"language":"Ukrainian","main-page":{"title":"Лабораторна робота номер 1","langs-select":"Виберіть мову, яку ви бажаєте:","langs":[{"disp-name":"Англійська","value":"English"},{"disp-name":"Українська","value":"Ukrainian"}],"description":"Це наше сховище соків. Ви можете додавати, редагувати та видаляти соки використовуючи відповідні кнопки знизу.","lv-title":"Список соків:","buttons":{"add-btn":"Додати","edit-btn":"Редагувати","del-btn":"Видалити"}},"add-offcanv":{"juce-name-label":"Введіть назву сока:","juce-manufacturer-label":"Введіть назву виробника сока:","juce-volume-label":"введіть обєм сока:","add-juce-btn":"Додати","clear-juce-btn":"Очистити","back-to-main-btn":"Назад"},"edit-offcanv":{"juce-name-label-edit":"Редагувати назву сока:","juce-manufacturer-label-edit":"Редагувати виробника сока:","juce-volume-label-edit":"Редагувати обєм сока:","save-juce-btn-edit":"Зберегти","clear-juce-btn-edit":"Очистити","back-to-main-btn-edit":"Назад"}}']

let juces = ['{"id":0,"name":"some","manufacturer":"some","volume":2E0}','{"id":1,"name":"some1","manufacturer":"some1","volume":1E0}']

document.addEventListener("DOMContentLoaded", event => 
{   
    updateJuceView(juces)
    setLocalizationFiles(json)
    createBindings()
    EnableVisualRowSelection();
    setupValidation();
});

function EnableVisualRowSelection()
{
    let lv = getElementById("list-view")       
    lv.style.setProperty("--bs-table-bg", "#ffffff00")
}

function createBindings()
{        
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

    getelementByQuery("button", "id", "langs").addEventListener("click", event =>
    {
        let dropDown = getelementByQuery("div", "id", "langs")
        let classes = dropDown.classList

        if(classes.contains("show"))//dropdown opened
        {
            classes.remove("show")
        }
        else//dropdown closed, need to open it
        {
            classes.add("show")
        }
    }
    )

    getElementById("edit-btn").addEventListener("click", event => 
    {
        let listView = getElementById("list-view")

        let tbody = listView.querySelector("tbody")

        let selRow = tbody.querySelector('tr[class="sel-row"]')

        selectedId = selRow.querySelector("th").innerHTML

        let data = selRow.querySelectorAll("td")

        let i = 0;
        for (const d of data) {
            if(i === 0)
            {
                getElementById("juce-name-edit").value = d.innerHTML
            }
            else if(i === 1)
            {
                getElementById("juce-manufacturer-edit").value = d.innerHTML
            }
            else
            {
                getElementById("juce-volume-edit").value = d.innerHTML
            }
            
            ++i
        }
    }
    )
}

function CleanChildren(htmlElement)
{
    if(htmlElement.hasChildNodes())
        {
            let child = htmlElement.lastElementChild;
            while (child) {
                htmlElement.removeChild(child);
                child = htmlElement.lastElementChild;
            }
        }
}

function updateJuceView(juceList)
{               
    let listView = getElementById("list-view")
    
    let tbody = listView.querySelector("tbody")

    CleanChildren(tbody)

    let i = 1;
    for (const juceStr of juceList)
    {       
        const juce = JSON.parse(juceStr)
     
        if(juce == undefined)
        {
            console.error("Unable to parce juceList parameter! function updateJuceView(juceList)")
        }

        let tr = document.createElement("tr")
        tr.setAttribute("id", `${i}`)
        let th = document.createElement("th")
        th.setAttribute("scope", "row")
        th.innerHTML = juce.id
        tr.appendChild(th)                

        let td_name = document.createElement("td")
        td_name.innerHTML = juce.name
        tr.appendChild(td_name)

        let td_manufacturer = document.createElement("td")
        td_manufacturer.innerHTML = juce.manufacturer
        tr.appendChild(td_manufacturer)

        let td_volume = document.createElement("td")
        td_volume.innerHTML = juce.volume
        tr.appendChild(td_volume)

        tr.addEventListener("click", function(e)
        {            
            //Remove selection from the already selected tr
            let elem = tbody.querySelector(`tr[id="${selectedJuce}"]`)

            if(elem && elem.classList.contains("sel-row"))
            {              
                elem.classList.remove("sel-row")
            }

            tr.classList.add("sel-row")
            selectedJuce = tr.getAttribute("id")
        }
        )

        tbody.appendChild(tr)

        ++i
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
        //Set Langs Selector
        FillLangSelectButton(localization, mainPage["langs"])
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

function FillLangSelectButton(selectedLanguage, langsArray)
{
    let sel_langs_button = getelementByQuery("button", "id", "langs")

    for (const lang of langsArray) {
        if(lang["value"] === selectedLanguage)
        {
            sel_langs_button.innerHTML = lang["disp-name"]
            break
        }
    }

    sel_langs_button.innerHTML = selectedLanguage    
}

function FillLangSelector(loc_file)
{     
    if(!loc_file) return
            
    let mainPage = loc_file["main-page"]
    let languages = mainPage["langs"]
    let lSelect = getelementByQuery("div", "id", "langs");    
    //Clear options if they exists
    CleanChildren(lSelect)
    
    languages.forEach((l) => {
        let option = document.createElement("a") 
        option.classList.add("dropdown-item")
        option.setAttribute("href", "#")
        option.setAttribute("name", l["value"])
        option.innerHTML = l["disp-name"]

        option.addEventListener("click", (event) => {
            let lang = event.target.name

            let drpDown = getelementByQuery("div", "id", "langs")

            if(drpDown.classList.contains("show"))
                drpDown.classList.remove("show")
            
            setLocalization(lang)            
        })           
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

function getelementByQuery(tagName, attribute, attribValue)
{
    let elem = document.querySelector(`${tagName}[${attribute}="${attribValue}"]`)

    if(!elem) 
    {
        console.error(`Unable to locate element with name: ${elemName}! Function - getElementByName(elemName)`)
        return undefined
    }
    
    return elem
}

function setupValidation()
{
    //Add Juce Validation Setup
    let inputElem = getElementById("juce-name")
    let feedback = getElementById("valid-feedback-juce-name")  
    let idsToCheck = ["juce-name", "juce-manufacturer", "juce-volume"]
    let submitBtn = getElementById("add-juce-btn")

    addValidatorToTheInput(inputElem, feedback, idsToCheck, submitBtn, canAdd)
    
    feedback = getElementById("valid-feedback-juce-name")      
    submitBtn = getElementById("add-juce-btn")

    addValidatorToTheInput(inputElem, feedback, idsToCheck, submitBtn, canEdit)
}

function addValidatorToTheInput(inputElement, feedBackElement, elemntIdsToValidate, submitButton, canSubmit)
{    
    if(validation.contains(inputElement.getAttribute("id")))
        validation.add(inputElement.getAttribute("id"), false)

    inputElement.addEventListener("input", event =>
        {        
            let classes = inputElement.classList            
            let error = ""
            let isValid = validateNotEmpty(event.target.value, (e) => error = e)
            validation.set(inputElement.getAttribute("id"), isValid)
            if(isValid)
            {                   
                classes.replace("is-invalid", "is-valid")                                           
            }
            else
            {
                if(classes.contains("is-valid"))
                    classes.remove("is-valid")
    
                classes.add("is-invalid")                        
            }
    
            feedBackElement.innerHTML = error  

            //Can press Submit
            canSubmit = validMap(validation, elemntIdsToValidate)
            if(canSubmit)
            {
                submitButton.classList.replace('btn-secondary', 'btn-primary')                
            }
            else
            {
                submitButton.classList.replace('btn-primary', 'btn-secondary')   
            }
        })
}

/////////////////////////////////VALIDATION/////////////////////////////////////////////////////////
//value is empty or undefined -> returns false, else returns true
//Also using function it can return the error
function validateNotEmpty(value, retErrorFunc)
{
    if(value == undefined)
    {
        retErrorFunc("Value was not set!")
        return false;
    }
        
    if(value === "")
    {
        retErrorFunc("Value was not set!")
        return false
    }
    
    retErrorFunc("")
    return true
}

function validMap(map, elemntIdsToValidate)
{
    for (const id of elemntIdsToValidate) 
    {
        if(!map.get(id))
            return false
    }

    return true
}


