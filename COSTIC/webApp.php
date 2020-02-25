<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>COSTIC</title>

<!-- Reset.css Pour mettre à 0 le CSS  -->
<link rel="stylesheet" href="reset.css">
</head>

<body>
		<!-- Affichage du formulaire  -->
    <form id="form1" name="form1" method="post" action="enveloppe.php">

		<p>DONNEES GENERALES</p>
    <table width="600" border="0">
        <tr>
            <td>Nom du Projet</td>
            <td><input name="champ1" type="text" id="champ1"></td>
        </tr>
        <tr>
            <td>Concerne un TOM ?</td>
						<td><select class="yesNoTom" name="yesNoTom" id="yesNoTom-select">
									<option value=""> --Choisir une réponse-- </option>
									<option value="Oui">Oui</option>
									<option value="Non">Non</option>
						</select>
						</td>
        </tr>
        <tr>
            <td>Adresse du bâtiment</td>
						<td><input name="champ2" type="text" id="champ2"></td>

        </tr>
        <tr>
            <td>Code Postal</td>
            <td><input name="champ3" type="text" id="champ3"></td>
        </tr>
				<tr>
						<td>Ville</td>
						<td><input name="champ4" type="text" id="champ4"></td>
				</tr>
				<tr>
						<td>Zone Climatique</td>
						<td>
              <input type="text" name="zoneClimatique" value="" id="zoneClimatique">
						</td>
				</tr>
        <tr>
					<td>Type d'énergie</td>
					<td><select class="typeEnergie" name="typeEnergie" id="typeEnergie-select">
								<option value=""> --Choisir une réponse-- </option>
								<option value="Combustible">Combustible</option>
								<option value="Electricité">Electricité</option>
					</select></td>
        </tr>
				<tr>
					<td>Surface totale chauffée</td>
					<td><input name="champ5" type="text" id="champ5"></td>
				</tr>
				<tr>
					<td>Bâtiment neuf/existant</td>
					<td><select class="typeBatiment" name="typeBatiment" id="typeBatiment-select">
								<option value=""> --Choisir une réponse-- </option>
								<option value="Existant">Existant</option>
								<option value="Neuf">Neuf</option>
					</select></td>
				</tr>
				<tr>
					<td>Secteur d'activité</td>
					<td><select class="typeActivite" name="typeActivite" id="typeActivite-select">
								<option value=""> --Choisir une réponse-- </option>
								<option value="Bureaux">Bureaux</option>
								<option value="Enseignement">Enseignement</option>
								<option value="Commerces">Commerces</option>
								<option value="Hôtellerie, Restauration">Hôtellerie, Restauration</option>
								<option value="Santé">Santé</option>
								<option value="Autres Secteurs">Autres Secteurs</option>
					</select></td>
				</tr>
				<tr>
					<td>Prix du kWh cumac</td>
					<td><input type="text" name="prixKWH" value="" id="prixKWH">€ / kWh cumac</td>
				</tr>
				<tr>
					<td><input type="submit" value="OK" name="Validez"></td>
					<td></td>
				</tr>
        </table>
    </form>

<!-- Connexion JS / CSS  propre a la page -->
<script type="text/javascript" src="app.js"></script>
<link rel="stylesheet" href="master.css">

</body>
</html>
