'use client';

import { PluginName, CompanyName, CompanyWebsite } from '@/src/define';

import * as Juce from 'juce-framework-frontend';

import AppBar from '@mui/material/AppBar';
import Stack from '@mui/material/Stack';
import Button from '@mui/material/Button';

import { useAboutStore } from '@/src/store/AboutStore';

import Menu from './Menu';

const visitWebsite = Juce.getNativeFunction('visitWebsite');

export default function App() {
  const { setOpen } = useAboutStore();

  return (
    <AppBar
      color="primary"
      enableColorOnDark
      sx={{
        position: 'static',
        px: 1,
        backgroundColor: 'var(--mui-palette-primary-darker)',
      }}
    >
      <Stack
        direction="row"
        alignItems="center"
        justifyContent="space-between"
        sx={{
          minHeight: 'var(--Header-minHeight)'
        }}
      >
        <Button
          onClick={() => setOpen(true)}
          variant="text"
          sx={{
            color: 'var(--mui-palette-common-white)',
            fontWeight: 'var(--mui-fontWeight-xl)',
          }}
          disableRipple
        >
          {PluginName}
        </Button>

        <Stack
          direction="row"
          alignItems="center"
          justifyContent="end"
          sx={{
            minHeight: 'var(--Header-minHeight)'
          }}
          spacing={2}
        >
          <Button
            onClick={() => visitWebsite(CompanyWebsite)}
            sx={{
              color: 'var(--mui-palette-common-white)',
              fontWeight: 'var(--mui-fontWeight-xl)',
            }}
            disableRipple
          >
            {CompanyName}
          </Button>
          <Menu />
        </Stack>
      </Stack>
    </AppBar>
  );
}
