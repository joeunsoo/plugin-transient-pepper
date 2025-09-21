'use client';

import { useEffect, useState } from 'react';
import * as Juce from 'juce-framework-frontend';
import { Box, Group, MenuItem, MenuLabel } from '@mantine/core';

const getWindowScale = Juce.getNativeFunction('getWindowScale');
const setWindowScale = Juce.getNativeFunction('setWindowScale');

export default function Page() {
  const [scale, setScale] = useState<number>(0);

  const handleClick = (_e: React.MouseEvent<HTMLButtonElement>, value: number) => {
    setScale(value);
    setWindowScale(value);
  };

  useEffect(() => {
    getWindowScale(100)
      // eslint-disable-next-line @typescript-eslint/ban-ts-comment
      // @ts-ignore
      .then((result: string) => {
        setScale(parseInt(result, 10));

        return null;
      })
      // eslint-disable-next-line no-console
      .catch(console.error);
  }, []);

  return (
    <>
      <MenuLabel>Scale</MenuLabel>
      {[100, 150, 200].map((value) => (
        <MenuItem key={value} onClick={(e) => handleClick(e, value)}>
          <Group
            align="center"
            justify="space-between"
            sx={{
              flexGrow: 1,
            }}
          >
            <Box>{value}%</Box>
            {value === scale && (
              <Box
                style={{
                  width: '0.6em',
                  height: '0.6em',
                  backgroundColor: 'var(--mantine-color-primary-5)',
                }}
              />
            )}
          </Group>
        </MenuItem>
      ))}
    </>
  );
}
