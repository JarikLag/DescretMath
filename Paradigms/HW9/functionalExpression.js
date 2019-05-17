"use strict";

var VARIABLES = {
    "x": 0,
    "y": 1,
    "z": 2
};

var operation = function (action) {
    return function () {
        var operands = arguments;
        return function () {
            var res = [];
            for (var i = 0; i < operands.length; i++) {
                res.push(operands[i].apply(null, arguments));
            }
            return action.apply(null, res);
        }
    }
};

var variable = function (name) {
    return function () {
        return arguments[VARIABLES[name]];
    }
};

for (var temp in VARIABLES) {
    this[temp] = variable(temp);
}

var cnst = function (value) {
    return function () {
        return value;
    };
};

var add = operation(function (a, b) {
    return a + b;
});

var subtract = operation(function (a, b) {
    return a - b;
});

var multiply = operation(function (a, b) {
    return a * b;
});

var divide = operation(function (a, b) {
    return a / b;
});

var negate = operation(function (a) {
    return -a;
});

var cube = operation(function (a) {
	return Math.pow(a, 3);
});

var cuberoot = operation(function (a) {
	return Math.pow(a, 1.0/3);
});

var expr = add(subtract(
    multiply(
        variable("x"),
        variable("x")
    ),
    multiply(
        cnst(2),
        variable("x")
    )), cnst(1));