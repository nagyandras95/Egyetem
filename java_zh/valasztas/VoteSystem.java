package valasztas;

public interface VoteSystem<T> {
    void closeVoting();

    long getCountFor(Parties party);

    Parties getWinner();

    int getVoteCount();

    void vote(Authorizable<T> voter, Parties party);
}