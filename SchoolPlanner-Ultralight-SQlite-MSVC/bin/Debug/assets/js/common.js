function data(d) {

	var dat = JSON.parse(d);

	var n = document.getElementById("name");
	n.innerHTML = dat["name"];

	var v = document.getElementById("version");
	v.innerHTML = dat["version"];
}

function setData(d) {
	var dat = JSON.parse(d);

	var n = document.getElementById("schoolName");
	n.innerHTML = dat["name"];
}

function returnJSON() {

	var json = {
		test: "from HTML",
		amount: 2.50
	};
	console.log("Testing errors from Javascript");
	returnData(JSON.stringify(json));

	changeView('main_menu');
}

function changeWidget(str) {
	changeView(str);
	toObject(str);
}