package expression;

public class Add extends AbstractBinaryOperator {
    public Add(final TripleExpression first, TripleExpression second) {
        super(first, second);
    }

    protected int calculate(final int first, final int second) {
        return first + second;
    }
}
