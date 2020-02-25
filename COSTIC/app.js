function colorBackGround()
{
  // valeur de retour du select
  var vRetour;
  vRetour = document.getElementById('yesNoEnv-select').value;
  if (vRetour == "Non") {
    // Changement de couleur du fond
    trGrey.style.backgroundColor="grey";
  }
  if (vRetour == "Oui") {
    trGrey.style.backgroundColor="white";
  }
}

// Deuxieme fonction similaire mais chaque ligne doit pouvoir etre independante
function colorBackGround2()
{
  // valeur de retour du select
  var vRetour;
  vRetour = document.getElementById('yesNoEnv-select-2').value;
  if (vRetour == "Non") {
    // Changement de couleur du fond
    trGrey2.style.backgroundColor="grey";
  }
  if (vRetour == "Oui") {
    trGrey2.style.backgroundColor="white";
  }
}

// Fonction réutilisable pour calculer le total
function typeActiviteCalcul(hValue, vSurface, typeActivite)
{
  var result = 0;

  if (typeActivite == "Bureaux/" || typeActivite == "Enseignement/" || typeActivite == "Commerces/" || typeActivite == "Autres Secteurs/") {
    var bureaux = 0.6;
    result = hValue * bureaux * vSurface;
  }
  if (typeActivite == "Santé/") {
    var bureaux = 1.3;
    result = hValue * bureaux * vSurface;
  }
  if (typeActivite == "Hôtellerie,") {
    var bureaux = 0.7;
    result = hValue * bureaux * vSurface;
  }
  return result;
}

function checkValueTotal()
{
  var valeurTotal = 0;
  var valeurL1 = 0;
  var valeurL2 = 0;

  valeurL1 = parseInt(document.getElementById('valeurFinal').value);
  valeurL2 = parseInt(document.getElementById('valeurFinal2').value);

  // Savoir si il y a une valeur dans la deuxieme case
  if (isNaN(valeurL2)) {
    valeurL2 = 0;
  }
  valeurTotal = parseInt(valeurL1) + parseInt(valeurL2);
  document.getElementById('valeurFinalAll').value = valeurTotal;
}

// Fonction de calcul principal pour la premiere ligne du tableau
function calcul()
{
  var zoneClimat;
  var typeEnergie;
  var typeActivite;
  var vSurface;
  var result = "Erreur";

  vSurface = document.getElementById('surfaceM2').value;
  zoneClimat = document.getElementById('zoneClimat').value;
  typeEnergie = document.getElementById('typeEnergie').value;
  typeActivite = document.getElementById('typeActivite').value;
  //alert(zoneClimat); //alert(typeEnergie); //alert(typeActivite);
  // condition de calcul
  // 3 paramettre dans une fonction est bien plus aurait ete un peu trop
  if (zoneClimat == "H1") {
    if (typeEnergie == "Combustible/") {
      var h1 = 2900;
      result = typeActiviteCalcul(h1, vSurface, typeActivite);
    }
    if (typeEnergie == "Electricité/") {
      var h1 = 1800;
      result = typeActiviteCalcul(h1, vSurface, typeActivite);
    }
  }
  if (zoneClimat == "H2") {
    if (typeEnergie == "Combustible/") {
      var h2 = 2400;
      result = typeActiviteCalcul(h1, vSurface, typeActivite);
    }
    if (typeEnergie == "Electricité/") {
      var h2 = 1500;
      result = typeActiviteCalcul(h1, vSurface, typeActivite);
    }
  }
  if (zoneClimat == "H3") {
    if (typeEnergie == "Combustible/") {
      var h3 = 1600;
      result = typeActiviteCalcul(h1, vSurface, typeActivite);
    }
    if (typeEnergie == "Electricité/") {
      var h1 = 1000;
      result = typeActiviteCalcul(h1, vSurface, typeActivite);
    }
  }
  // Debug perso -> alert("Surface = " + vSurface);
  //Changement de la valeur final apres le calcul
  document.getElementById('valeurFinal').value = result;

  checkValueTotal();
}

// Fonction de calcul principal pour la deuxieme ligne du tableau
function calcul2()
{
  var zoneClimat;
  var typeEnergie;
  var typeActivite;
  var vSurface;
  var result = "Erreur";

  vSurface = document.getElementById('surfaceM2-2').value;
  zoneClimat = document.getElementById('zoneClimat').value;
  typeEnergie = document.getElementById('typeEnergie').value;
  typeActivite = document.getElementById('typeActivite').value;
  //alert(zoneClimat); //alert(typeEnergie); //alert(typeActivite);
  // condition de calcul
  // 3 paramettre dans une fonction est bien plus aurait ete un peu trop
  if (zoneClimat == "H1") {
    if (typeEnergie == "Combustible/") {
      var h1 = 4800;
      result = typeActiviteCalcul(h1, vSurface, typeActivite);
    }
    if (typeEnergie == "Electricité/") {
      var h1 = 3000;
      result = typeActiviteCalcul(h1, vSurface, typeActivite);
    }
  }
  if (zoneClimat == "H2") {
    if (typeEnergie == "Combustible/") {
      var h2 = 3900;
      result = typeActiviteCalcul(h1, vSurface, typeActivite);
    }
    if (typeEnergie == "Electricité/") {
      var h2 = 2500;
      result = typeActiviteCalcul(h1, vSurface, typeActivite);
    }
  }
  if (zoneClimat == "H3") {
    if (typeEnergie == "Combustible/") {
      var h3 = 2600;
      result = typeActiviteCalcul(h1, vSurface, typeActivite);
    }
    if (typeEnergie == "Electricité/") {
      var h1 = 1600;
      result = typeActiviteCalcul(h1, vSurface, typeActivite);
    }
  }
  // Debug perso -> alert("Surface = " + vSurface);
  //Changement de la valeur final apres le calcul
  document.getElementById('valeurFinal2').value = result;
  checkValueTotal();
}

























function ModifChampText()
    {
      //   ma fonction doit récuperer toutes les valeures de la page précédente
      //   pour l'envoyer a la prochaine page
        if (form1.champ1.value!="")
            {
                alert(form1.champ1.value);
                // alert("Champ 1 vide");
            }
        if (form1.champ2.value!="")
            {
              alert(form1.champ2.value);
               //alert("Champ 2 vide");
            }
        if (form1.champ3.value!="")
            {
              alert(form1.champ3.value);
                //alert("Champ 3 Vide");
            }
        if (form1.champ4.value!="")
            {
              alert(form1.champ4.value);

            }
          if (form1.champ5.value!="")
            {
            alert(form1.champ5.value);
            }
          if (form1.prixKWH.value!="")
          {
            alert(form1.prixKWH.value);
          }
        else
            {
              //form1.zoneClimatique.value=form1.champ5.value;
              //form1.Total_champ.value=form1.champ1.value+"\n"+form1.champ2.value+"\n"+form1.champ3.value;
            }
    }
