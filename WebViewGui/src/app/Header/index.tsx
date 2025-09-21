'use client';

import { PluginName, CompanyName, mantineSpace, secondaryMain } from '@/define';

import { Box, Group, rem } from '@mantine/core';
import Button from '@/ui/BlurButton';

import JuceToggleBypass from '@/ui/Control/ToggleButton/JuceToggleBypass';
import { uesControlStore } from '@/store/ControlStore';

import Menu from './Menu';

export default function App() {
  const { setBypass } = uesControlStore();

  return (
    <Box
      px={rem(mantineSpace * 1)}
      py={rem(mantineSpace * 1.5)}
    >
      <Group
        align="center"
        justify="space-between"
        sx={{
          minHeight: 'var(--Header-minHeight)'
        }}
      >
        <Group
          align="center"
          justify="start"
          gap={rem(mantineSpace * 2)}
        >
          <JuceToggleBypass
            identifier="bypassToggle"
            onChange={(e, value) => setBypass(value)}
            ignoreBypass
            invertValue
          />
          <Button
            variant="text"
            color={secondaryMain}
            fw={'var(--mui-fontWeight-xl)'}
          >
            {PluginName}
          </Button>
        </Group>

        <Group
          align="center"
          justify="end"
          gap={rem(mantineSpace * 3)}
        >
          <Button
            color="white"
            fw={'var(--mui-fontWeight-xl)'}
            sx={{
              fontSize: 'var(--mui-fontSize-xs)',
            }}
          >
            {CompanyName}
          </Button>
          <Menu />
        </Group>
      </Group>
    </Box>
  );
}
