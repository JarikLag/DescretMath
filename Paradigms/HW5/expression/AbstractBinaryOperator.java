package expression;

public strictfp abstract class AbstractBinaryOperator implements AnyExpression {
    final private AnyExpression first;
    final private AnyExpression second;

    public AbstractBinaryOperator(AnyExpression first, AnyExpression second) {
        this.first = first;
        this.second = second;
    }

    protected abstract int calculate(int first, int second);

    protected abstract double calculate(double first, double second);

    public int evaluate(int x) {
        return calculate(first.evaluate(x), second.evaluate(x));
    }

    public double evaluate(double x) {
        return calculate(first.evaluate(x), second.evaluate(x));
    }
}
