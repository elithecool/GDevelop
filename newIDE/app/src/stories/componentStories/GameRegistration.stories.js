// @flow
import * as React from 'react';

import muiDecorator from '../ThemeDecorator';
import paperDecorator from '../PaperDecorator';

import { GameRegistration } from '../../GameDashboard/GameRegistration';
import GDevelopJsInitializerDecorator, {
  testProject,
} from '../GDevelopJsInitializerDecorator';
import {
  fakeIndieAuthenticatedUser,
  fakeNotAuthenticatedAuthenticatedUser,
} from '../../fixtures/GDevelopServicesTestData';
import AuthenticatedUserContext from '../../Profile/AuthenticatedUserContext';
import withMock from 'storybook-addon-mock';
import { GDevelopGameApi } from '../../Utils/GDevelopServices/ApiConfigs';

export default {
  title: 'GameDashboard/GameRegistration',
  component: GameRegistration,
  decorators: [paperDecorator, muiDecorator, GDevelopJsInitializerDecorator],
};

export const NoProjectLoaded = () => (
  <AuthenticatedUserContext.Provider value={fakeIndieAuthenticatedUser}>
    <GameRegistration project={null} onGameRegistered={() => {}} />
  </AuthenticatedUserContext.Provider>
);

export const NotLoggedIn = () => (
  <AuthenticatedUserContext.Provider
    value={fakeNotAuthenticatedAuthenticatedUser}
  >
    <GameRegistration
      project={testProject.project}
      onGameRegistered={() => {}}
    />
  </AuthenticatedUserContext.Provider>
);

export const NotAuthorized = () => (
  <AuthenticatedUserContext.Provider value={fakeIndieAuthenticatedUser}>
    <GameRegistration
      project={testProject.project}
      onGameRegistered={() => {}}
    />
  </AuthenticatedUserContext.Provider>
);
NotAuthorized.decorators = [withMock];
NotAuthorized.parameters = {
  mockData: [
    {
      url: `${GDevelopGameApi.baseUrl}/game/?userId=indie-user`,
      method: 'GET',
      status: 403,
      response: {},
      delay: 500,
    },
  ],
};

export const GameNotExisting = () => (
  <AuthenticatedUserContext.Provider value={fakeIndieAuthenticatedUser}>
    <GameRegistration
      project={testProject.project}
      onGameRegistered={() => {}}
    />
  </AuthenticatedUserContext.Provider>
);
GameNotExisting.decorators = [withMock];
GameNotExisting.parameters = {
  mockData: [
    {
      url: `${GDevelopGameApi.baseUrl}/game/?userId=indie-user`,
      method: 'GET',
      status: 404,
      response: {},
      delay: 500,
    },
  ],
};

export const ErrorLoadingGame = () => (
  <AuthenticatedUserContext.Provider value={fakeIndieAuthenticatedUser}>
    <GameRegistration
      project={testProject.project}
      onGameRegistered={() => {}}
    />
  </AuthenticatedUserContext.Provider>
);
ErrorLoadingGame.decorators = [withMock];
ErrorLoadingGame.parameters = {
  mockData: [
    {
      url: `${GDevelopGameApi.baseUrl}/game/?userId=indie-user`,
      method: 'GET',
      status: 500,
      response: {},
      delay: 500,
    },
  ],
};

export const RegisteredWithGameStatsEmail = () => (
  <AuthenticatedUserContext.Provider value={fakeIndieAuthenticatedUser}>
    <GameRegistration
      project={testProject.project}
      onGameRegistered={() => {}}
      suggestGameStatsEmail
    />
  </AuthenticatedUserContext.Provider>
);
RegisteredWithGameStatsEmail.decorators = [withMock];
RegisteredWithGameStatsEmail.parameters = {
  mockData: [
    {
      url: `${GDevelopGameApi.baseUrl}/game/?userId=indie-user`,
      method: 'GET',
      status: 200,
      response: {
        id: 'game-id',
        name: 'My game',
      },
      delay: 500,
    },
  ],
};

export const RegisteredWithLoader = () => (
  <AuthenticatedUserContext.Provider value={fakeIndieAuthenticatedUser}>
    <GameRegistration
      project={testProject.project}
      onGameRegistered={() => {}}
    />
  </AuthenticatedUserContext.Provider>
);
RegisteredWithLoader.decorators = [withMock];
RegisteredWithLoader.parameters = {
  mockData: [
    {
      url: `${GDevelopGameApi.baseUrl}/game/?userId=indie-user`,
      method: 'GET',
      status: 200,
      response: {
        id: 'game-id',
        name: 'My game',
      },
      delay: 500,
    },
  ],
};

export const RegisteredWithoutLoader = () => (
  <AuthenticatedUserContext.Provider value={fakeIndieAuthenticatedUser}>
    <GameRegistration
      project={testProject.project}
      onGameRegistered={() => {}}
      hideLoader
    />
  </AuthenticatedUserContext.Provider>
);
RegisteredWithoutLoader.decorators = [withMock];
RegisteredWithoutLoader.parameters = {
  mockData: [
    {
      url: `${GDevelopGameApi.baseUrl}/game/?userId=indie-user`,
      method: 'GET',
      status: 200,
      response: {
        id: 'game-id',
        name: 'My game',
      },
      delay: 500,
    },
  ],
};
