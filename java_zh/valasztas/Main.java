package valasztas;

import valasztas.ArrayVoteSystem;
import valasztas.HashVoteSystem;
import valasztas.VoteSystem;
import valasztas.Voter;

public class Main {
    public static void main(String[] args) {
        Voter v1 = new Voter("Bela", "id1", 25, 1461);
        Voter v2 = new Voter("Jozsi", "id2", 52, 141);
        Voter v3 = new Voter("Laci", "id3", 42, 666);

        VoteSystem<VoterKey> vs = new ArrayVoteSystem<>();

        vs.vote(v1, Parties.JAVA_HEROES);
        vs.vote(v2, Parties.JAVA_HEROES);
        try {
            vs.vote(v1, Parties.CPP_FANS);
        } catch (AlreadyVoted av) {
            System.err.println(av);
        }
        vs.vote(v3, Parties.HASKELL_MAGES);
        vs.closeVoting();

        System.out.println("vote count: " + vs.getVoteCount());
        System.out.println("The winner is: " + vs.getWinner());
    }
}