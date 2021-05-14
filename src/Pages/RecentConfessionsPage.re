open Belt;

type state = {
  recentConfessions: ConfessionData.recentConfessions,
  loading: bool,
  fetchError: bool,
};

type action =
  | Load(ConfessionData.recentConfessions)
  | Loading
  | FetchErrorOccured;

let initialState = {
  recentConfessions: [||],
  loading: true,
  fetchError: false,
};

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Loading => {...state, loading: true}
        | Load(data) =>
          let confessionsOrderedNewestToLatest = Array.reverse(data);
          {
            ...state,
            recentConfessions: confessionsOrderedNewestToLatest,
            loading: false,
          };
        | FetchErrorOccured => {...state, fetchError: true}
        },
      initialState,
    );

  React.useEffect0(() => {
    let callback = result => {
      switch (result) {
      | None => dispatch(FetchErrorOccured)
      | Some(confessions) => dispatch(Load(confessions))
      };
    };
    Api.fetchConfessions(callback);
    None;
  });

  let renderConfessions = () =>
    <div>
      {state.recentConfessions
       ->Array.mapWithIndex((index, confession) =>
           <RecentConfessionsListItem key={confession.id} index confession />
         )
       ->React.array}
    </div>;

  switch (state) {
  | {fetchError: true} => <ErrorMessage />

  | {loading: true} => <LoadingMessage />

  | {loading: false, fetchError: false} => renderConfessions()
  };
};
