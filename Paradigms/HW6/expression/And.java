package expression;

public class And extends AbstractBinaryOperator {
    public And(final TripleExpression first, final TripleExpression second) {
        super(first, second);
    }

    protected int calculate(final int first, final int second) {
        return first & second;
    }
}
