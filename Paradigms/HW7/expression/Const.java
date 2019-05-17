package expression;

public class Const implements TripleExpression {
    private final Number value;

    public Const(final Number value) {
        this.value = value;
    }

    public int evaluate(final int x, final int y, final int z) {
        return value.intValue();
    }
}
