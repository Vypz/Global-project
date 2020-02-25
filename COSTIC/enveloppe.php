<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>COSTIC</title>

<!-- Reset.css Pour mettre à 0 le CSS  -->
<link rel="stylesheet" href="reset.css">
</head>

<?php
// Récuperation des valeur POST pour ensuite faire passer les valeurs dans le DOM avec l'input hidden
$zoneClimat = htmlspecialchars($_POST['zoneClimatique']);
$typeEnergie = htmlspecialchars($_POST['typeEnergie']);
$typeActivite = htmlspecialchars($_POST['typeActivite']);
$surfaceChauffe = htmlspecialchars($_POST['champ5']);

 ?>

<!-- Tableau récapitulatif des données générales  -->
<body>

  <form id="form2" name="form2" class="" action="" method="post">

      <table>
        <tr>
          <td><p>Données générales</p></td>
          <td></td>
        </tr>
        <tr>
          <td>Zone Climatique</td>
          <td> <?php echo $zoneClimat ?> </td>
        </tr>
        <tr>
          <td>Type d'énergie</td>
          <td> <?php echo  $typeEnergie ?> </td>
        </tr>
        <tr>
          <td>Secteur d'activité</td>
          <td> <?php echo  $typeActivite ?> </td>
        </tr>
        <tr>
          <td>Surface chauffée</td>
          <td> <?php echo  $surfaceChauffe ?> </td>
        </tr>
      </table>
    </form>

    <!-- Choix des opérations  -->
    <!-- Class tdP pour effectuer les Modification sur le 2eme tableau  -->

    <table class="table2">
      <tr>
        <td>Choix</td>
        <td>Opération standardisées possibles</td>
        <td>Caractéristiques</td>
        <td>Surface</td>
        <td>Montant</td>
      </tr>
      <tr>
        <td></td>
        <td></td>
        <td>Montant Total</td>
        <td></td>
        <td><input name="valeurFinalAll" type="text" id="valeurFinalAll">kWh cumac</td>
      </tr>
      <!-- trGrey est la pour changer la ligne en fonction du oui ou non  -->
      <!-- Première vrai ligne du tableau  -->
      <tr class="trGrey" id="trGrey">
        <td><select class="yesNoEnv" name="yesNoEnv" id="yesNoEnv-select" onchange='colorBackGround()'>
              <option value="Oui">Oui</option>
              <option value="Non">Non</option></select></td>
        <td><a href="#">BAT-EN-101 : Isolation de combles ou de toitures</a></td>
        <td>R ≥6 m².K/W</td>
        <td><input name="surfaceM2" type="text" id="surfaceM2" onchange='calcul()'></td>
        <td><input name="valeurFinal" type="text" id="valeurFinal">kWh cumac</td>
      </tr>

      <!-- Deuxieme ligne du tableau  -->
      <tr class="trGrey2" id="trGrey2">
        <td><select class="yesNoEnv-2" name="yesNoEnv-2" id="yesNoEnv-select-2" onchange='colorBackGround2()'>
              <option value="Oui">Oui</option>
              <option value="Non">Non</option></select></td>
        <td><a href="#">BAT-EN-102 : Isolation des murs</a></td>
        <td>R ≥3,7 m².K/W</td>
        <td><input name="surfaceM2-2" type="text" id="surfaceM2-2" onchange='calcul2()'></td>
        <td><input name="valeurFinal2" type="text" id="valeurFinal2">kWh cumac</td>
      </tr>
    </table>

    <!-- Récupération de la variable php et transfer de la valeur par le DOM  -->
    <input type=hidden id="zoneClimat" value=<?php echo $zoneClimat; ?> />
    <input type=hidden id="typeEnergie" value=<?php echo $typeEnergie; ?>/>
    <input type=hidden id="typeActivite" value=<?php echo $typeActivite; ?>/>
    <input type=hidden id="surfaceChauffe" value=<?php echo $surfaceChauffe; ?>/>

    <p> Modification des données générales, <a href="webApp.php">ICI</a> </p>

  <!-- Connexion CSS propre a la page  -->
  <script type="text/javascript" src="app.js"></script>
  <link rel="stylesheet" href="enveloppe.css">
</body>
