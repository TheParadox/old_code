function setOption(btn) {
	var val = btn.innerHTML;

	document.getElementById("currentResolution").innerHTML = val;
}

function resetActive() {
	var dropBtns = document.getElementsByClassName("option");
	for (var i = 0; i < dropBtns.length; i++) {
		dropBtns[i].className = dropBtns[i].className.replace("active", "");
	}
}

window.onclick = function (event) {
	if (!event.target.matches('.dropbtn')) {
		var dropdowns = document.getElementsByClassName("dropdown-content");
		var i;
		for (i = 0; i < dropdowns.length; i++) {
			var openDropdown = dropdowns[i];
			if (openDropdown.classList.contains('show')) {
				openDropdown.classList.remove('show');
			}
		}
	}

	if (event.target.matches('.dropbtn')) {
		document.getElementById("resDropdown").classList.toggle("show");
	}

	if (event.target.className == "option") {
		resetActive();
		document.getElementById("currentResolution").innerHTML = event.target.innerHTML;
		event.target.className += " active";
	}
}

function setCurrentOptions(d) {
	var data = JSON.parse(d);

	var resDropdown = document.getElementById("resDropdown");
	var current = data["screenResID"];

	for (var i = 0; i < data["resolutions"].length; i++) {
		var button = "<button class='option";

		if (i == current) {
			button += " active";
		}
		button += "'>" + data["resolutions"][i][0] + " x " + data["resolutions"][i][1] + "</button>";

		resDropdown.innerHTML += button;
	}

	document.getElementById("currentResolution").innerHTML = data["resolutions"][current][0] + " x " + data["resolutions"][current][1];


	var fullscreen = data["fullscreen"];
	document.getElementById("fullscreenCheckbox").checked = fullscreen;
}