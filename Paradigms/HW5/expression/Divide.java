package expression;

public strictfp class Divide extends AbstractBinaryOperator {
    public Divide(AnyExpression first, AnyExpression second) {
        super(first, second);
    }

    protected int calculate(int first, int second) {
        return first / second;
    }

    protected double calculate(double first, double second) {
        return first / second;
    }
}
