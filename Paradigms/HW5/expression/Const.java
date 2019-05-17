package expression;

public strictfp class Const implements AnyExpression {
    private final Number value;

    public Const(Number value) {
        this.value = value;
    }

    public double evaluate(double x) {
        return value.doubleValue();
    }

    public int evaluate(int x) {
        return value.intValue();
    }
}
