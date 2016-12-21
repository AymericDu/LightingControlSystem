$("#intensity-slider").slider();
$("#intensity-slider").on("slide", function(slideEvt) {
	$("#intensity-value").text(slideEvt.value);
});

$("#luminosity-slider").slider();
$("#luminosity-slider").on("slide", function(slideEvt) {
	$("#luminosity-value").text(slideEvt.value);
});
