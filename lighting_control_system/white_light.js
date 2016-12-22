$("#intensity-slider").slider();
$("#intensity-slider").on("slide", function(slideEvt) {
	$("#intensity-value").text(slideEvt.value);
});

$("#luminosity-slider").slider();
$("#luminosity-slider").on("slide", function(slideEvt) {
	$("#luminosity-value").text(slideEvt.value);
});

function ajax_intensity () {
  var intensity = $("#intensity-slider").slider("getValue");
	ajax_light(intensity, intensity, intensity);
}

$("#intensity-validate").click(ajax_intensity);

function ajax_luminosity () {
  var luminosity = $("#luminosity-slider").slider("getValue");
	$.ajax({
      url: "../luminosity?l=" + luminosity,
      dataType: "text",
			timeout: 10000
    })
    .done(function(msg) {
      if (msg != "OK") {
        $("#error").fadeIn().delay(10000).fadeOut();
      }
    })
    .fail(function() {
      $("#error").fadeIn().delay(10000).fadeOut();
    });
}

$("#luminosity-validate").click(ajax_luminosity);
