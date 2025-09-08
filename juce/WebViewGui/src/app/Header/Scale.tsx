'use client';

import * as Juce from 'juce-framework-frontend';

import Box from '@mui/material/Box';
import Stack from '@mui/material/Stack';
import MenuItem from '@mui/material/MenuItem';
import ListSubheader from '@mui/material/ListSubheader';
import { useEffect, useState } from 'react';

const getWindowScale = Juce.getNativeFunction('getWindowScale');
const setWindowScale = Juce.getNativeFunction('setWindowScale');

type PageProps = {
  onClick?: React.MouseEventHandler<HTMLLIElement>
}

export default function Page({
  onClick
}: PageProps) {
  const [scale, setScale] = useState<number>(0);

  const handleClick = (e: React.MouseEvent<HTMLLIElement>, value: number) => {
    if (onClick) {
      onClick(e);
    }
    setScale(value);
    setWindowScale(value);
  };

  useEffect(() => {
    // eslint-disable-next-line @typescript-eslint/ban-ts-comment
    // @ts-ignore
    getWindowScale(100).then((result: string) => {
      setScale(parseInt(result, 10));

      return null;
    }).catch(null);
  }, []);

  return (
    <>
      <ListSubheader className="cursorDefault">
        Scale
      </ListSubheader>
      {[100, 150, 200].map((value) => (
        <MenuItem
          key={value}
          onClick={(e) => handleClick(e, value)}
        >
          <Stack
            direction="row"
            alignItems="center"
            justifyContent="space-between"
            sx={{
              flexGrow:1
            }}
          >
            <Box>
              {value}%
            </Box>
            {value === scale &&
              <Box
                sx={{
                  width: '0.6em',
                  height: '0.6em',
                  backgroundColor: 'var(--mui-palette-primary-light)'
                }}
              />
            }
          </Stack>
        </MenuItem>
      ))}
    </>
  );
}
