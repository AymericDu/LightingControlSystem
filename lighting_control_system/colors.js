$("#color-picker").colorpicker({
  customClass: "colorpicker-2x",
  sliders: {
    saturation: {
      maxLeft: 200,
      maxTop: 200
    },
    hue: {
      maxTop: 200
    },
    alpha: {
      maxTop: 200
    }
  },
  color: "#000000",
  container: true,
  inline: true
});

function ajax_color () {
  var color = $("#color-picker").colorpicker("getValue");
  var r = parseInt(color.substr(1, 2), 16);
  var g = parseInt(color.substr(3, 2), 16);
  var b = parseInt(color.substr(5, 2), 16);
	ajax_light(r, g, b);
}

$("#color-validate").click(ajax_color);
