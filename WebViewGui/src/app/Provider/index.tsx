import MuiProvider from './MuiProvider';
import MantineProvider from './MantineProvider';
import AboutProvider from './AboutProvider';
import AnalysisDataProvider from './AnalysisDataProvider';
import SnackbarProvider from './SnackbarProvider';
import ControlParameterProvider from './ControlParameterProvider';
import ActivateProvider from './ActivateProvider';
import IsDebug from './IsDebug';
import GlobalSpaceListener from './GlobalSpaceListener';

type ProviderProps = {
  children: React.ReactNode
}

export default function Provider({
  children
}: ProviderProps) {
  return (
    <MuiProvider>
      <MantineProvider>
        {children}
        <GlobalSpaceListener />
        <IsDebug />
        <ActivateProvider />
        <AboutProvider />
        <AnalysisDataProvider />
        <SnackbarProvider />
        <ControlParameterProvider />
      </MantineProvider>
    </MuiProvider>
  );
}
