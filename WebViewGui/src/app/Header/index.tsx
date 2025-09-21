'use client';

import { Box, Group, rem } from '@mantine/core';
import { CompanyName, mantineSpace, PluginName, secondaryMain } from '@/define';
import { useControlStore } from '@/store/ControlStore';
import Button from '@/ui/BlurButton';
import JuceToggleBypass from '@/ui/Control/ToggleButton/JuceToggleBypass';
import Menu from './Menu';

export default function App() {
  const { setBypass } = useControlStore();

  return (
    <Box px={rem(mantineSpace * 1)} py={rem(mantineSpace * 1.5)}>
      <Group
        align="center"
        justify="space-between"
        sx={{
          minHeight: 'var(--Header-minHeight)',
        }}
      >
        <Group align="center" justify="start" gap={rem(mantineSpace * 2)}>
          <JuceToggleBypass
            identifier="bypassToggle"
            onChange={(_e, value) => setBypass(value)}
            ignoreBypass
            invertValue
          />
          <Button variant="text" color={secondaryMain} fw={700}>
            {PluginName}
          </Button>
        </Group>

        <Group align="center" justify="end" gap={rem(mantineSpace * 3)}>
          <Button
            color="white"
            fw={700}
            sx={{
              fontSize: 'var(--mantine-font-size-xs)',
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
