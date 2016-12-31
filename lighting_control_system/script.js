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

function ajax_interrupt () {
  if ($("#switch-led").prop("checked")) {
    ajax_light(255, 255, 255);
  } else {
    ajax_light(0, 0, 0);
  }
}

function change_interrupt (r, g, b) {
  if (r == 0 & g == 0 & b == 0) {
    if ($("#switch-led").prop("checked")) {
      //$("body").off("change", "#switch-led", ajax_interrupt);
      $("#switch-led").bootstrapToggle("off");
      //$("body").on("change", "#switch-led", ajax_interrupt);
    }
  } else {
    if (!$("#switch-led").prop("checked")) {
      //$("body").off("change", "#switch-led", ajax_interrupt);
      $("#switch-led").bootstrapToggle("on");
      //$("body").on("change", "#switch-led", ajax_interrupt);
    }
  }
}

function change_color (r, g, b) {
  $("#color").css("background-color","rgb("+r+","+g+","+b+")");
}

function change_intensity (r, g, b) {
  $("#intensity").text(((r + g + b) / 3).toFixed(2));
}

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

function ajax_get_value_light_sensor() {
  $.ajax({
    url: "../light_sensor",
    dataType: "text"
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

ajax_get_light();
setInterval(ajax_get_value_light_sensor, 500);
$("body").on("change", "#switch-led", ajax_interrupt);
