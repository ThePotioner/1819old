import { gql } from 'apollo-server';

const typeDefs = gql`
    type Song {
        id : Int!
        rank: Int!
        name: String!
        artist: String!
        album: String!
        img: String!
    }
    
    type Query {
        songs: [Song!]!
        song(id: Int!): Song 
    }

    type Mutation {
        addSong(name: String!, artist: String!, album: String!, img: String!): Song!
    }
`;

export default typeDefs;