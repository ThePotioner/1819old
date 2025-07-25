import songlists from '../database/songlists';

const resolvers = {
    Query: {
        songs: () => songlists,
        song: (_, { rank }) => {
            return songlists.filter(song => song.rank === rank)[0];
        }
    },
    Mutation: {
        addSong: (_, { name, artist, album, img }) => {
            if (songlists.find(song => song.name === name)) return null;

            const newSong = {
                id : songlists.length + 1,
                rank: songlists.length + 1,
                name: name,
                artist: artist,
                album: album,
                img: img
            };

            songlists.push(newSong);

            return newSong;
        }
    }
}

export default resolvers;