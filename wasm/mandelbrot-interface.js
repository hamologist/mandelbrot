var ctx = document.getElementById("mandelbrotDisplay").getContext("2d"),
    rgbaOne = {
      'red': 122,
      'green': 66,
      'blue': 244,
      'alpha': 255
    },
    rgbaTwo = {
      'red': 234,
      'green': 115,
      'blue': 51,
      'alpha': 255
    },
    mandelbrotConfig = {
      'x_c': -1.0,
      'y_c': 0,
      'zoom': 1,
      'max_iterations': 1000,
      'escape_point': 4,
      'view_width': 1440,
      'view_height': 900,
      'first_color': rgbaOne,
      'second_color': rgbaTwo
    },
    cleanViewData = function (viewData) {
      var y = viewData.size()-1,
          x = 0,
          viewRow = null;

      while (y >= 0) {
        viewData.get(y).delete();
        y--;
      }
      viewData.delete();
    },
    rgbBuilder = function (viewPixel) {
      return 'rgb(' + viewPixel.red + ', ' + viewPixel.green + ', ' + viewPixel.blue + ')';
    },
    renderFrame = function (viewData) {
      var y = viewData.size()-1,
          x = 0,
          viewRow = null,
          viewPixel = null;

      while (y >= 0) {
        viewRow = viewData.get(y);
        x = viewRow.size()-1;
        while (x >= 0) {
          viewPixel = viewRow.get(x);
          ctx.fillStyle = rgbBuilder(viewPixel);
          ctx.fillRect(x, y, 1, 1);
          x--;
        }
        y--;
      }
    };

var Module = {
  onRuntimeInitialized: function() {
    var viewData = Module.mandelbrot_compute(mandelbrotConfig);
    renderFrame(viewData);
    cleanViewData(viewData);
  }
};

window.onload = function () {
  var xInput = document.getElementById("xInput"),
      yInput = document.getElementById("yInput"),
      zoom = document.getElementById("zoom"),
      maxIterations = document.getElementById("maxIterations"),
      escapePoint = document.getElementById("escapePoint"),
      computeButton = document.getElementById("computeButton");

  computeButton.addEventListener("click", function() {
    var viewData = null;
    mandelbrotConfig.x_c = parseFloat(xInput.value);
    mandelbrotConfig.y_c = parseFloat(yInput.value);
    mandelbrotConfig.zoom = parseFloat(zoom.value);
    mandelbrotConfig.max_iterations = parseInt(maxIterations.value);
    mandelbrotConfig.escape_point = parseInt(escapePoint.value);

    viewData = Module.mandelbrot_compute(mandelbrotConfig);
    renderFrame(Module.mandelbrot_compute(mandelbrotConfig));
    viewData.delete();
  });
}
