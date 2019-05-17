"use strict";

var VARIABLES = {"x": 0, "y": 1, "z": 2};

function Const(x) {
    this.getValue = function () {
        return x;
    };
}
Const.prototype.toString = function () {
    return this.getValue().toString();
};
Const.prototype.evaluate = function () {
    return this.getValue();
};

function Variable(s) {
    var ind = VARIABLES[s];
    this.getName = function () {
        return s;
    };
    this.getInd = function () {
        return ind;
    };
}
Variable.prototype.toString = function () {
    return this.getName();
};
Variable.prototype.evaluate = function () {
    return arguments[this.getInd()];
};

var Operation = new function () {
    this.toString = function() {
        var res = [];
        for (var i = 0; i < this.operands.length; i++) {
            res.push(this.operands[i].toString());
        }
        return res.join(" ") + " " + this.symbol;
    };
    this.evaluate = function() {
        var res = [];
        for (var i = 0; i < this.operands.length; i++) {
            res.push(this.operands[i].evaluate.apply(this.operands[i], arguments));
        }
        return this.action.apply(null, res);
    };
};

var Operation = {
    toString : function() {
        var res = [];
        for (var i = 0; i < this.operands.length; i++) {
            res.push(this.operands[i].toString());
        }
        return res.join(" ") + " " + this.symbol;
    }, 
    evaluate : function() {
        var res = [];
        for (var i = 0; i < this.operands.length; i++) {
            res.push(this.operands[i].evaluate.apply(this.operands[i], arguments));
        }
        return this.action.apply(null, res);
    }
};

var operationFactory = function(action, symbol) {
    var res = function () {
        this.operands = arguments;
        this.action = action;
        this.symbol = symbol;
    };
    res.prototype = Operation;
    return res;
};

var Add = new operationFactory(
    function (a, b) {
        return a + b;
    },
    "+");

var Subtract = new operationFactory(
    function (a, b) {
        return a - b;
    },
    "-");

var Multiply = new operationFactory(
    function (a, b) {
        return a * b;
    },
    "*");

var Divide = new operationFactory(
    function (a, b) {
        return a / b;
    },
    "/");

var Negate = new operationFactory(
    function (a) {
        return -a;
    },
    "negate");

var Square = new operationFactory(
    function (a) {
        return a * a;
    },
    "square");

var Sqrt = new operationFactory(
    function (a) {
        return Math.sqrt(Math.abs(a));
    },
    "sqrt");