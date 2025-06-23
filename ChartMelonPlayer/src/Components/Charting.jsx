import React, { useState } from 'react';
import axios from 'axios';
import TitleBar from 'frameless-titlebar';
import { css } from 'emotion';
import { Button, Menu } from 'antd';
import SongItem from './SongItem';

const Charting = () => {
  const [chartData, setChartData] = useState({});
  const [loading, setLoading] = useState(false);
  const [isloaded, setIsLoaded] = useState(false);

  const loadData = async () => {
    const { data } = await axios.get('http://localhost:3001/api');
    setChartData(data);
    setLoading(false);
    setIsLoaded(true);
  };

  const syncLoading = () => {
    setLoading(true);
    loadData();
  };

  const regenLoading = () => {
    // setLoading(true);
  };

  return (
    <>
      <TitleBar app="&nbsp;ChartMelon Player" />
      <Menu mode="horizontal">
        <Menu.Item disabled>
          <Button type="primary" loading={loading} onClick={syncLoading}>
          Sync
          </Button>
        &nbsp;
          <Button type="danger" loading={false} onClick={regenLoading}>
          DB Regen
          </Button>
        </Menu.Item>
      </Menu>
      <div className={style}>
        {
          isloaded
            ? <SongItem data={chartData} />
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
