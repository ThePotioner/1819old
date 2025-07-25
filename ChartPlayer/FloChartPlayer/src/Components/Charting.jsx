import React, { useState } from 'react';
import axios from 'axios';
import TitleBar from 'frameless-titlebar';
import { css } from 'emotion';
import { Button, Menu } from 'antd';
import SongItem from './SongItem';
import { gql, useMutation } from '@apollo/client';
import { useQuery } from '@apollo/react-hooks';

const ADD_SONG = gql`
  mutation AddSong($name: String!, $artist: String!, $album: String!, $img: String!) {
    addSong(name: $name, artist: $artist, album: $album, img: $img) {
      id
      name
      artist
      album
      img
    }
  }
`;

const GET_SONGLIST = gql`
  {
    songs {
      rank
      name
      artist
      album
      img
    }
  }
`;

const Charting = () => {
  const [addSong, { songdata }] = useMutation(ADD_SONG);
  const [chartData, setChartData] = useState({});
  const [loading, setLoading] = useState(false);
  const [isloaded, setIsLoaded] = useState(false);
  const { loading_, error, data } = useQuery(GET_SONGLIST);

  const jsonLoading = async () => {
    const { data } = await axios.get('https://www.music-flo.com/api/meta/v1/chart/track/1');
    setChartData(data.data);
    console.log("ok.");
  };

  const syncLoading = () => {
    setLoading(true);
    setLoading(false);
    console.log(data?.songs);
    setIsLoaded(true);
  };

  const regenLoading = async () => {
    chartData.trackList.forEach(song => {
      console.log(song.name, song.artistList[0].name, song.album.title, song.album.imgList[5].url);
      addSong({ variables: { name: song.name, artist: song.artistList[0].name, album: song.album.title, img: song.album.imgList[5].url } });
    });
  };

  return (
    <>
      <TitleBar app="&nbsp;FloChart Player" />
      <Menu mode="horizontal">
        <Menu.Item disabled>
          <Button type="primary" loading={loading} onClick={syncLoading}>
          Sync
          </Button>
        &nbsp;
          <Button type="danger" loading={false} onClick={regenLoading}>
          DB Regen
          </Button>
        &nbsp;
          <Button type="primary" loading={false} onClick={jsonLoading}>
          Get JSON
          </Button>
        </Menu.Item>
      </Menu>
      <div className={style}>
        {
          isloaded
            ? <SongItem data={data?.songs} />
            : <span>차트를 불러오시려면 Sync 버튼을 눌러주세요!</span>
        }
      </div>
    </>
  );
};

const style = css`
  overflow-y: auto;
  overflow-x: hidden;
  position: absolute;
  top: 76px;
  bottom: 0;
  left: 0;
  right: 0;
  margin-left: 10px;

  ::-webkit-scrollbar {
  width: 10px;
  height: 10px; 
  }

  ::-webkit-scrollbar-thumb {
    background: rgba(90, 90, 90);
  }

  ::-webkit-scrollbar-track {
    background: rgba(0, 0, 0, 0.2);
  }
`;

export default Charting;
