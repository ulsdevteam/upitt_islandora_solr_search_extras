<?php
/**
 * @file
 * islandora-solr-extras.tpl.php
 *
 * Variables available:
 * - $results: Primary profile results array
 *
 * @see template_preprocess_islandora_solr()
 */

?>
<?php if (empty($results)): ?>
  <p class="no-results"><?php print t('Sorry, but your search returned no results.'); ?></p>
<?php else: ?>
  <div class="islandora islandora-solr-search-results">
    <?php $row_result = 0; ?>
    <?php foreach($results as $key => $result): ?>
      <!-- Search result -->
      <div class="islandora-solr-search-result clear-block <?php print $row_result % 2 == 0 ? 'odd' : 'even'; ?>">
        <div class="islandora-solr-search-result-inner">
          <div class="search-result-wrapper">
            <div class="search-result-img-wrapper">
            <!-- Thumbnail -->
              <?php print $result['thumbnail']; ?>
            </div>
          </div>
          <!-- Metadata -->
          <?php if ($result['page_thumbnail']) : ?>
          <ul class="solr-page-thumb">
              <li>
                 <?php print $result['page_thumbnail']; ?>
             </li>
          </ul>
          <?php endif; ?>
          <ul class="solr-fields islandora-inline-metadata">
            <?php foreach($result['page_solr_doc'] as $key => $value): ?>
              <li class="solr-value solr-field-orig <?php print $value['class']; ?>">
                <div class="solr-label">
                   <?php print $value['label']; ?>
                </div>
              </li>
            <?php endforeach; ?>
          </ul>
          <ul class="solr-fields islandora-inline-metadata">
            <?php foreach($result['solr_doc'] as $key => $value): ?>
              <li class="solr-value solr-field-parent <?php print $value['class']; ?>">
                <div class="solr-label">
                   <?php print $value['label']; ?>
                </div>
                <div class="solr-fieldvalue">
                  <?php print $value['value']; ?>
                </div>
              </li>
            <?php endforeach; ?>
          </ul>
        </div>
      </div>
    <?php $row_result++; ?>
    <?php endforeach; ?>
  </div>
<?php endif; ?>

