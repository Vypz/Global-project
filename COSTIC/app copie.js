
function ModifChampText()
    {
        if (form1.champ1.value=="")
            {
                form1.champ1.style.backgroundColor="red";
                alert("Champ 1 vide");
            }
        if (form1.champ2.value=="")
            {
               alert("Champ 2 vide");
            }
        if (form1.champ3.value=="")
            {
                alert("Champ 3 Vide");
            }
        else
            {
              form1.Total_champ.value=form1.champ1.value+"\n"+form1.champ2.value+"\n"+form1.champ3.value;
            }
    }
