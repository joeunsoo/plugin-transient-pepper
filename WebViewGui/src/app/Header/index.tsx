'use client';

import { PluginName, CompanyName, mantineSpace } from '@/define';

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
            sx={{
              color: 'var(--mui-palette-secondary-main)',
              fontWeight: 'var(--mui-fontWeight-xl)',
            }}
            disableRipple
          >
            {PluginName}
          </Button>
        </Group>

        <Group
          align="center"
          justify="end"
          gap={rem(mantineSpace * 2)}
        >
          <Button
            sx={{
              color: 'var(--mui-palette-common-white)',
              fontSize: 'var(--mui-fontSize-xs)',
              fontWeight: 'var(--mui-fontWeight-xl)',
            }}
            disableRipple
          >
            {CompanyName}
          </Button>
          <Menu />
        </Group>
      </Group>
    </Box>
  );
}
