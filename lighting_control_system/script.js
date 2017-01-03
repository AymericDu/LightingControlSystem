/*
 * Envoie une requête sur la MBED pour définir la couleur de la LED.
 */
function ajax_light (r, g, b) {
  $.ajax({
      url: "../light?r=" + r + "&g=" + g + "&b=" + b,
      dataType: "text",
			timeout: 10000
    })
    .done(function(msg) {
      if (msg != (r + "-" + g + "-" + b)) {
        $("#error").fadeIn().delay(10000).fadeOut();
      }
    })
    .fail(function() {
      $("#error").fadeIn().delay(10000).fadeOut();
    });
}

/*
 * Fonction attachée au bouton de l'interface permettant d'éteindre ou d'allumer la LED.
 */
function ajax_interrupt () {
  if ($("#switch-led").prop("checked")) {
    ajax_light(255, 255, 255);
  } else {
    ajax_light(0, 0, 0);
  }
}

/*
 * Met à jour l'état de l'interrupteur en fonction de la couleur de la LED.
 */
function change_interrupt (r, g, b) {
  if (r == 0 & g == 0 & b == 0) {
    if ($("#switch-led").prop("checked")) {
      $("body").off("change", "#switch-led", ajax_interrupt);
      $("#switch-led").bootstrapToggle("off");
      $("body").on("change", "#switch-led", ajax_interrupt);
    }
  } else {
    if (!$("#switch-led").prop("checked")) {
      $("body").off("change", "#switch-led", ajax_interrupt);
      $("#switch-led").bootstrapToggle("on");
      $("body").on("change", "#switch-led", ajax_interrupt);
    }
  }
}

/*
 * Change la couleur de la LED dans l'interface web.
 */
function change_color (r, g, b) {
  $("#color").css("background-color","rgb("+r+","+g+","+b+")");
}

/*
 * Change la valeur de l'intensité dans l'interface web.
 */
function change_intensity (r, g, b) {
  $("#intensity").text(((r + g + b) / 3).toFixed(2));
}

/*
 * Récupère la couleur de la LED et met à jour l'interrupteur, la couleur et
 * l'intensité sur l'interface web.
 */
function ajax_get_light () {
  $.ajax({
      url: "../light",
      dataType: "text",
			timeout: 10000
    })
    .done(function(msg) {
      var rgb = msg.split("-");
      var r = parseInt(rgb[0]);
      var g = parseInt(rgb[1]);
      var b = parseInt(rgb[2]);
      change_interrupt(r,g,b);
      change_color(r,g,b);
      change_intensity(r,g,b);
    })
    .fail(function() {
      $('#error').fadeIn().delay(10000).fadeOut();
    });
}

/*
 * Récupère la valeur du capteur de lumière.
 */
function ajax_get_value_light_sensor() {
  $.ajax({
    url: "../light_sensor",
    dataType: "text",
    timeout: 10000
  })
  .done(function(msg) {
    var digits = "0".repeat(4 - msg.length).concat(msg);
    var children = $("#four-digits").children();
    for(var i = 0; i < 4 /*children.length*/; i++) {
      children[i].innerHTML = digits[i];
    }
  })
  .fail(function() {
    $("#error").fadeIn().delay(10000).fadeOut();
  });
}

/*
 * Met à jour l'interrupteur, la couleur et l'intensité sur l'interface web
 * lorsqu'il y a un changement d'état.
 */
function update_interface() {
  $.ajax({
    url: "../comet_light",
    dataType: "text"
  })
  .done(function(msg) {
    var rgb = msg.split("-");
    var r = parseInt(rgb[0]);
    var g = parseInt(rgb[1]);
    var b = parseInt(rgb[2]);
    change_interrupt(r,g,b);
    change_color(r,g,b);
    change_intensity(r,g,b);
  })
  .fail(function() {
    $('#error').fadeIn().delay(10000).fadeOut();
  })
  .always(function() {
    update_interface();
  });
}

$("body").on("change", "#switch-led", ajax_interrupt);
ajax_get_light();
setInterval(ajax_get_value_light_sensor, 500);
update_interface();
