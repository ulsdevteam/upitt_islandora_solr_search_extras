<?php

/**
 * @file
 * Handles the display/submission of the admin settings form for this module.
 */

/**
 * Defines the admin settings form.
 *
 * @param array $form
 *   The Drupal form definition.
 * @param array $form_state
 *   The Drupal form state.
 *
 * @return array
 *   The Drupal form definition.
 */
function upitt_islandora_solr_search_extras_admin_settings(array $form, array &$form_state) {
  $form = array(
    'wrapper' => array(
      '#type' => 'fieldset',
      '#title' => t('Map collection url to a Solr search for members of that collection.'),
      '#description' => t('When clicked, this will create or modify url_alias records for all collection pages.  This also adds an extra "landing" parameter that can be used on search landing page to display meta heading info.'),
      'createurls' => array(
        '#type' => 'submit',
        '#value' => 'Create / update Collection urls',
      ),
    ),
    'showparent_searchresults' => array(
      '#type' => 'checkbox',
      '#title' => t('Show parent info for any collection items in search results.'),
      '#description' => t('When enabled, will show the parent item information for any collection items in search results.'),
      '#default_value' => variable_get('upitt_islandora_solr_search_extras_showparent_searchresults', 0),
    ),
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save configuration'),
    ),
    'reset' => array(
      '#type' => 'submit',
      '#value' => t('Reset to defaults'),
    ),
  );

  return $form;
}

/**
 * Function that sets the Drupal variables with user's input.
 *
 * @param array $form
 *   The Drupal form definition.
 * @param array $form_state
 *   The Drupal form state.
 */
function upitt_islandora_solr_search_extras_admin_settings_submit(array $form, array &$form_state) {
  drupal_set_message(t('The settings have been updated!'));
  $id = $form_state['triggering_element']['#id'];
  switch ($id) {
    case 'edit-submit':
      variable_set('upitt_islandora_solr_search_extras_showparent_searchresults', $form_state['values']['showparent_searchresults']);
      break;

    case 'edit-createurls':
      _map_url_alias_for_collection_pages();
      break;

    case 'edit-reset':
      variable_del('upitt_islandora_solr_search_extras_showparent_searchresults');
      break;
  }
}

function _map_url_alias_for_collection_pages() {
  // run a Solr search to get all collection labels
  module_load_include('inc', 'islandora_solr_search', 'includes/utilities');
  $query_processor = new IslandoraSolrQueryProcessor();
  $query_processor->solrQuery = 'RELS_EXT_hasModel_uri_ms:info\:fedora\/islandora\:collectionCModel AND PID:pitt\:* AND -fgl_label_s:["" TO *]';
  $query_processor->solrStart = 0;
  $query_processor->solrLimit = 9999;
  $query_processor->solrParams = array(
    'fl' => 'PID,fgs_label_s',
    'fq' => '',
  );
  $url = parse_url(variable_get('islandora_solr_url', 'localhost:8080/solr'));
  $solr = new Apache_Solr_Service($url['host'], $url['port'], $url['path'] . '/');
  $solr->setCreateDocuments(FALSE);
  try {
    $search_results = $solr->search($query_processor->solrQuery, $query_processor->solrStart, $query_processor->solrLimit, $query_processor->solrParams, 'GET');
    $tmp = json_decode($search_results->getRawResponse(), TRUE);
    $results = array();
    $numFound = $tmp['response']['numFound'];
    if ($tmp['response']['numFound'] > 0) {
      foreach ($tmp['response']['docs'] as $k=>$rec) {
        $results[$rec['PID']] = $rec['fgs_label_s'];
      }
    }
    $update_count = 0;
    foreach ($results as $pid=>$result) {
      $source = 'islandora/search_collection/' . $pid;
      $alias = _format_collection_url($result);
      $alias2 = 'islandora/object/' . $pid;
      // db_query('DELETE FROM {url_alias} WHERE alias = :alias', array(':alias' => $alias));
      // db_query('REPLACE INTO {url_alias} (`source`, `alias`, `language`) VALUES (:source, :alias, \'und\')',
      //   array(':source' => $source, ':alias' => $alias));
      // db_query('REPLACE INTO {url_alias} (`source`, `alias`, `language`) VALUES (:source, :alias, \'und\')',
      //   array(':source' => $source, ':alias' => $alias2));
      $update_count++;
      // dpm('clean_label = "' . $clean_label .'"');
      dpm('DELETE FROM url_alias WHERE alias = \'' . $alias . '\';' . "\n" .
          'REPLACE INTO url_alias (`source`, `alias`, `language`) VALUES (\'' . $source . '\', \'' . $alias . '\', \'und\');' . "\n" .
          'REPLACE INTO url_alias (`source`, `alias`, `language`) VALUES (\'' . $source . '\', \'' . $alias2 . '\', \'und\');');
    }
    drupal_set_message(number_format($numFound) . t(' collections were found') . '<br>' .
      number_format($update_count) . t(' url_alias records were updated or created.'), 'info');
    // dpm($results);
  }
  catch (Exception $e) {
    drupal_set_message(t('There was a problem generating the url_alias records.<br>') . print_r($e, true), 'warning');
    error_log('EXCEPTION in _save_solr_search_session : called from ' . $_SERVER['SERVER_NAME'] .
' - ' . $_SERVER['REQUEST_URI'] . '
' . print_r($e, true));
    $skey = '';
  }
  return;
}

