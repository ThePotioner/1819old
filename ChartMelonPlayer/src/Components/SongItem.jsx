import React, { useState, useCallback, useEffect } from 'react';
import PropTypes from 'prop-types';
import { List, Avatar } from 'antd';

const SongItem = ({ data }) => {
  const [initLoading, setInitLoading] = useState(true);
  const [isLoading, setIsLoading] = useState(false);

  const initLoadCallBack = useCallback(() => {
    setInitLoading(false);
    if (data) {
      setIsLoading(true);
    }
  }, [data]);

  useEffect(initLoadCallBack, [data, initLoadCallBack]);

  return (isLoading
    ? (
      <List
        className="song-chart"
        loading={initLoading}
        itemLayout="horizontal"
        dataSource={data}
        renderItem={(src) => (
          <List.Item>
            <List.Item.Meta
              avatar={<Avatar src={src.Img} />}
              title={src.Name}
              description={`${src.Artist.substring(0, src.Artist.length / 2)} [${src.Album}]`}
            />
          </List.Item>
        )}
      />
    ) : null
  );
};

SongItem.propTypes = {
  data: PropTypes.object.isRequired,
};

export default SongItem;
